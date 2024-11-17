//
// Created by Saxion on 2018-12-30.
//

#include <gtest/gtest.h>
#include <map>
#include <algorithm>

int main(int argc, char** argv) {

    std::map<std::string, double> points{
            {"has_all_tasks_assigned", 0.5},
            {"has_task_with_deadline_afer", 0.5},
            {"remove_asignee_from_all", 1.0},
            {"extend_deadlines", 0.5},
            {"count_tasks_with_deadlines_before", 0.5},
            {"add_assignee_to_task", 1.0},
            {"get_tasks_with_priority", 0.5},
            {"extract_tasks_with_deadline_before", 1.0},
            {"list_sorted_by_prio", 1.0},
            {"remove_all_finished", 0.5},
            {"get_nth_to_complete", 0.5},
            {"get_first_n_to_complete", 0.5},
            {"cost_burndown", 1.5},
            {"cheapest_and_most_expensive", 0.5},
            {"total_cost", 0.5},
            {"total_cost_of", 1.0},
            {"separate_by_deadline", 0.5},
            {"estimate_workload", 1.0},
            {"average_cost_of_prio", 1.0}
    };

    ::testing::InitGoogleTest(&argc, argv);

    ::testing::UnitTest& unit_test = *::testing::UnitTest::GetInstance();

//    ::testing::TestEventListeners& listeners = unit_test.listeners();

    auto ret_val = RUN_ALL_TESTS();
    // print detailed output diagnostics


    auto& out = std::cout;

    auto sum{0.0};

    for (auto i = 0; i < unit_test.total_test_case_count(); ++i) { // for each suite
        const auto& test_case = *unit_test.GetTestCase(i);
        for (auto j = 0; j < test_case.total_test_count(); ++j) { // for each test case in a suite
            const auto& test_info = *test_case.GetTestInfo(j);

            if (test_info.result()->Passed()){
                sum += points[test_info.name()];
            }

        }
    }

    out << "\n\nYou've scored (approximately) " << (sum > 10.0 ? 10.0 : sum) << " points.\n";

    return ret_val;
}