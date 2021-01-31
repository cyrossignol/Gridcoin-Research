#include "neuralnet/greylist.h"

using namespace NN;

GreylistSnapshot Greylist::Filter(WhitelistSnapshot projects)
{
    GreylistSnapshot::ActiveProjectSet active_projects;
    GreylistSnapshot::GreylistedProjectSet greylisted_projects;

    for (const auto& project : projects) {
        const GreylistReasons reasons = Check(project);

        if (reasons.empty()) {
            active_projects.emplace_back(&project);
        } else {
            greylisted_projects.emplace_back(&project, reasons);
        }
    }

    return GreylistSnapshot(
        std::move(projects),
        std::move(active_projects),
        std::move(greylisted_projects));
}

GreylistReasons Greylist::Check(const Project& project)
{
    return Check(project.m_name);
}

GreylistReasons Greylist::Check(const std::string& project_name)
{
    // TODO: implement greylist rules

    GreylistReasons reasons;

    // Stub... return empty vector.
    return reasons;
}
