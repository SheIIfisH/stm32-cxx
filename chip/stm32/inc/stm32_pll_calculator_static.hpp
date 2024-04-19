#ifndef STM32f4_PLL_CALCULATOR_STATIC_H_
#define STM32f4_PLL_CALCULATOR_STATIC_H_

#include <stdint.h>

namespace sys
{
#if defined(STM32F42xxx) || defined(STM32F43xxx)
	template <
		uint_fast32_t SysClockFreq,	          // Defines required system clock
		uint_fast32_t InFreq    = 16'000'000, // Input frequency from HSI, HSE or PLL
		uint_fast32_t Per48Freq = 30'000'000, // if peripherial 48 MHz clocks are disabled, set to zero
		uint_fast32_t MinVcoFreq = 100'000'000,
		uint_fast32_t MaxVcoFreq = 432'000'000,
		uint_fast32_t MinInVcoFreq = 1'000'000,
		uint_fast32_t MaxInVcoFreq = 2'000'000,
		uint_fast32_t MinQ = 2,
		uint_fast32_t MaxQ = 15,
		uint_fast32_t MinM = 2,
		uint_fast32_t MaxM = 63,
		uint_fast32_t MinN = 50,
		uint_fast32_t MaxN = 432
	>

	class stm32_pll_calculator_static
	{
	private:
		enum class Factor { N, M, P, Q };

		static constexpr uint16_t calc_by_q_m_p(Factor factor, uint16_t q, uint16_t m, uint16_t p)
		{
			unsigned n = (uint64_t) SysClockFreq * (uint64_t)m * (uint64_t)p / (uint64_t)InFreq;
			if (n <= MinN) return 0;
			if (n >= MaxN) return 0;

			unsigned test_sysfreq = (uint64_t) InFreq * (uint64_t)n / (m * p);
			if (test_sysfreq != SysClockFreq)
				return 0;

			if (Per48Freq != 0)
			{
				unsigned test_usbfreq = (uint64_t) InFreq * (uint64_t)n / (m * q);
				if (test_usbfreq != Per48Freq)
					return 0;
			}

			return
				(factor == Factor::N) ? n :
				(factor == Factor::M) ? m :
				(factor == Factor::P) ? p :
				(factor == Factor::Q) ? q :
				0;
		}

		static constexpr uint16_t calc_by_q_m(Factor factor, uint16_t q, uint16_t m)
		{
			unsigned vco_in_freq = InFreq / m;
			if (vco_in_freq <= MinInVcoFreq) return 0;
			if (vco_in_freq >= MaxInVcoFreq) return 0;
			if (vco_in_freq % Per48Freq != 0)  return 0;

			auto res2 = calc_by_q_m_p(factor, q, m, 2);
			if (res2 != 0) return res2;

			auto res4 = calc_by_q_m_p(factor, q, m, 4);
			if (res4 != 0) return res4;

			auto res6 = calc_by_q_m_p(factor, q, m, 6);
			if (res6 != 0) return res6;

			return calc_by_q_m_p(factor, q, m, 8);
		}

		static constexpr uint16_t calc_by_q_m_loop(Factor factor, uint16_t q, uint16_t m)
		{
			auto res = calc_by_q_m(factor, q, m);
			if (res != 0)
				return res;
			else if (m <= MaxM)
				return calc_by_q_m_loop(factor, q, m + 1);
			return 0;
		}

		static constexpr uint16_t calc_by_q(Factor factor, uint16_t q)
		{
			unsigned VcoFreq = Per48Freq * q;
			if (VcoFreq <= MinVcoFreq) return 0;
			if (VcoFreq >= MaxVcoFreq) return 0;

			return calc_by_q_m_loop(factor, q, MinM);
		}

		static constexpr uint16_t calc_by_q_loop(Factor factor, uint16_t q)
		{
			auto res = calc_by_q(factor, q);
			if (res != 0)
				return res;
			else if (q <= MaxQ)
				return calc_by_q_loop(factor, q + 1);
			return 0;
		}

		static constexpr uint16_t calc(Factor type)
		{
			if (type == Factor::Q && Per48Freq == 0) return MinQ;

			if (Per48Freq != 0)
				return calc_by_q_loop(type, MinQ);
			else
				return calc_by_q_m_loop(type, MinQ, MinM);
		}

	public:
		// Division factor for the main PLL (PLL) input clock
		static constexpr uint16_t pll_m = calc(Factor::M);

		// Main PLL (PLL) multiplication factor for VCO
		static constexpr uint16_t pll_n = calc(Factor::N);

		// Main PLL (PLL) division factor for main system clock
		static constexpr uint16_t pll_p = calc(Factor::P);

		// Main PLL (PLL) division factor for USB OTG FS, and SDIO clocks
		static constexpr uint16_t pll_q = calc(Factor::Q);

		static_assert(
			SysClockFreq <= 180'000'000,
			"SysclockFreq is incorrect"
			);

		static_assert(
			Per48Freq <= 48'000'000,
			"PerFreq is incorrect"
			);

		static_assert(
			pll_m && pll_n && pll_p && pll_q,
			"Combination of SysclockFreq, HseFreq and Clk48Freq is incorrect"
			);
	};
#endif
}

#endif
