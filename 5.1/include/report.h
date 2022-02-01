/*
 *  report.h
 *
 *  Date: January 31st 2022
 *  Author: Paul Mauviel
 */

#ifndef REPORT_H
#define REPORT_H

#include <cstdint>
#include <vector>
#include <string>

// This is an immutable pure data class -- no need for encapsulation.
struct ReportRow {
    ReportRow(uint64_t month, double opening, double deposited, double monthlyInterest) :
        Month(month),
        OpeningAmount(opening),
        DepositedAmount(deposited),
        TotalAmount(opening + deposited),
        Interest(TotalAmount * monthlyInterest),
        ClosingBalance(TotalAmount + Interest)
        {};

    const uint64_t Month;
    const double OpeningAmount;
    const double DepositedAmount;
    const double TotalAmount;
    const double Interest;
    const double ClosingBalance;
};

// Pure data class for specifying input parameters for constructing a report
struct ReportParameters {
    double InitialInvestment { 0.f };
    double MonthlyDeposit { 0.f };
    double AnnualInterest { 0.f };
    uint64_t NumberOfMonths { 0 };
};

class Report {
public:
    // marked as noexcept as there can be errors when using emplace_back and throwing exceptions
    explicit Report(std::string  title, const ReportParameters& params) noexcept;

    void printYearly(int width) const;
private:
    std::vector<ReportRow> m_Rows;
    std::string m_Title;
};

#endif