//
// Created by dop on 2/13/21.
//

#ifndef PROJ1_STATISTICSUI_H
#define PROJ1_STATISTICSUI_H

#include <iostream>
#include "ui/OptionUI.h"
#include "statistics.h"
#include "ui/MixedColumn.h"

using namespace std::placeholders;

class StatsUI : public OptionUI, public Statistics<long>
{
public:
    StatsUI() = default;

    void showCurrentState() override;

    void init() override;

    void loadFileOptionHandler(std::string&& path);

    template <class WideString = std::wstring, typename Func>
    std::function<void(void)> statsDisplayAdapter(WideString name, Func statsGetter);

    template <typename Func>
    std::function<void(void)> quartilesDisplayAdapter(Func quartilesGetter);

    template <typename Func>
    Table* frequencyTableToUITable(Func frequencyTableGetter);

    template <typename Func>
    std::function<void(void)> frequencyTableDisplayAdapter(Func frequencyTableGetter);

    void displayAllResultAndWriteToFile();
};

#endif //PROJ1_STATISTICSUI_H
