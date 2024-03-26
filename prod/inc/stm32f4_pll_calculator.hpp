#ifndef STM32_PLL_CALCULATOR_H
#define STM32_PLL_CALCULATOR_H

#include <stdint.h>

template <
	unsigned SysclockFreq,	       // Defines required system clock
	unsigned PerFreq = 48'000'000, // if peripherial clocks are disabled, set to zero
	unsigned HseFreq = 0,          // if HSE unused keep it as zero
	unsigned HsiFreq = 16'000'000,
	unsigned MinVcoFreq = 100'000'000,
	unsigned MaxVcoFreq = 432'000'000,
	unsigned MinInVcoFreq = 1'000'000,
	unsigned MaxInVcoFreq = 2'000'000,
	unsigned MinQ = 2,
	unsigned MaxQ = 15,
	unsigned MinM = 2,
	unsigned MaxM = 63,
	unsigned MinN = 50,
	unsigned MaxN = 432
>

class stm32f4_pll_calculator
{
private:
	enum class Factor { N, M, P, Q };

	static constexpr uint16_t calc_by_q_m_p(Factor factor, uint16_t q, uint16_t m, uint16_t p)
	{
		unsigned n = (uint64_t) SysclockFreq * (uint64_t)m * (uint64_t)p / (uint64_t)InFreq;
		if (n <= MinN) return 0;
		if (n >= MaxN) return 0;

		unsigned test_sysfreq = (uint64_t) InFreq * (uint64_t)n / (m * p);
		if (test_sysfreq != SysclockFreq)
			return 0;

		if (PerFreq != 0)
		{
			unsigned test_usbfreq = (uint64_t) InFreq * (uint64_t)n / (m * q);
			if (test_usbfreq != PerFreq)
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
		if (vco_in_freq % PerFreq != 0)  return 0;

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
		unsigned VcoFreq = PerFreq * q;
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
		if (type == Factor::Q && PerFreq == 0) return MinQ;

		if (PerFreq != 0)
			return calc_by_q_loop(type, MinQ);
		else
			return calc_by_q_m_loop(type, MinQ, MinM);
	}

private:
	static constexpr uint64_t InFreq = (uint64_t)(HseFreq == 0) ? HsiFreq : HseFreq;

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
		SysclockFreq <= 180'000'000,
		"SysclockFreq is incorrect"
		);

	static_assert(
		PerFreq <= 48'000'000,
		"PerFreq is incorrect"
		);

	static_assert(
		(HseFreq == 0) || ((HseFreq >= 4'000'000) && (HseFreq <= 26'000'000)),
		"HseFreq is incorrect"
		);

	static_assert(
		pll_m && pll_n && pll_p && pll_q,
		"Combination of SysclockFreq, HseFreq and Clk48Freq is incorrect"
		);
};

#endif
