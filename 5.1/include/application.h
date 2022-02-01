/*
 *  application.h
 *
 *  Date: January 31st 2022
 *  Author: Paul Mauviel
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include <string>
#include <report.h>
#include <tuple>

class Application {
public:
    explicit Application(unsigned char terminalWidth);
    void run();

private:
    ReportParameters readReportParameters();

private:
    unsigned char m_TerminalWidth;
    bool m_Running;

    // TODO: view previous reports menu
    // Vector of report pairs. First element is without monthly deposits, second with
    std::vector<std::pair<Report, Report>> m_PreviousReports;
    const std::string m_TerminalLine;

};

#endif