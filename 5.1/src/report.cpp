/*
 *  report.cpp
 *
 *  Date: January 31st 2022
 *  Author: Paul Mauviel
 */

#include "report.h"

#include <iostream>
#include <iomanip>

Report::Report(std::string title, const ReportParameters &params) noexcept : m_Title{std::move(title)} {

    // Use Report Parameters to build rows
    ReportRow* lastRow = nullptr;
    double totalInvestment = params.InitialInvestment;
    for (size_t i = 0; i < params.NumberOfMonths; i++) {
        if (lastRow) totalInvestment = lastRow->ClosingBalance;
        lastRow = &m_Rows.emplace_back(static_cast<uint64_t>(i+1), totalInvestment, params.MonthlyDeposit, params.AnnualInterest / 12.f);
    }
}

void Report::printYearly(int width) const{
    const std::string doubleLine(width, '=');
    const std::string line(width, '-');

    std::cout << doubleLine << '\n';
    std::cout << std::string((width / 2) - m_Title.length() / 2, ' ') << std::right << m_Title << '\n';
    std::cout << doubleLine << '\n';

    auto wColOne = std::setw(static_cast<long long>(static_cast<float>(width) * (1.f/15.f)));
    auto wOtherCol = std::setw(static_cast<long long>(static_cast<float>(width) * (0.475)));

    std::cout << std::setfill(' ') << wColOne << std::right << "Year"
        << std::setfill(' ') << wOtherCol << std::right <<  "Year End Balance"
        << std::setfill(' ') << wOtherCol << std::right <<   "Interest Earned\n";
    std::cout << line << std::endl;


    double interestEarned { 0.0 };
    for (size_t currentMonth = 0; currentMonth < m_Rows.size(); currentMonth++) {
        auto& currentRow = m_Rows[currentMonth];
        interestEarned += currentRow.Interest;

        if (currentMonth != 0 && currentMonth % 12 == 11) {
            uint64_t year { (currentMonth / 12) + 1};
            double endBalance = currentRow.ClosingBalance;

            std::cout << std::setfill(' ') << wColOne << std::right << year
                      << std::setfill(' ') << std::fixed << std::setprecision(2) << wOtherCol << std::right <<  endBalance
                      << std::setfill(' ') << wOtherCol << std::right <<   interestEarned << '\n';

            interestEarned = 0;
        }
    }
}