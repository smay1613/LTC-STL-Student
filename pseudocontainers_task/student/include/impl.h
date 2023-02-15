#pragma once
#include <string>
#include <map>
#include <unordered_map>
#include <iostream>
#include <tuple>
#include <algorithm>

using calendar = std::string; // format: o - available, x - vacation
using worker_id = size_t;
using days = size_t;
constexpr days daysInMonth = 30;
constexpr char availableMarker = 'o';
constexpr char vacationMarker = 'x';

size_t getMaxIntersectionCount(const calendar& workerVacation1, const calendar& workerVacation2)
{
    size_t count = 0;

    for (size_t i = 0; i < daysInMonth; i++)
    {
        if (workerVacation1.at(i) == vacationMarker && workerVacation2.at(i) == vacationMarker)
            count++;
    }

    return count;
}

struct worker_pair
{
    worker_id _id1;
    worker_id _id2;

    worker_pair() = default;
    worker_pair(const worker_id& id1, const worker_id& id2)
        : _id1(id1), _id2(id2)
    {
        if (_id1 > _id2)
            std::swap(_id1, _id2);
    }

    bool operator==(const worker_pair& p) const
    {
        return std::tie(_id1, _id2) == std::tie(p._id1, p._id2);
    }
};

namespace std
{
    template<>
    struct hash<worker_pair>
    {
        size_t operator()(const worker_pair& p) const
        {
            return std::hash<size_t>{}(p._id1 + p._id2);
        }
    };
}

bool is_same_worker(const worker_id& id1, const worker_id& id2)
{
    return id1 == id2;
}

std::tuple<worker_id, worker_id, days> findWorkerPairMaxIntersection(const std::unordered_map<worker_pair, days>& vacationIntersections)
{
    std::pair<worker_pair, days> highestPair{};

    std::for_each(vacationIntersections.begin(), vacationIntersections.end(),
        [&](const std::pair<worker_pair, days>& p)
        {
            if (p.second > highestPair.second)
                highestPair = p;
        }
    );

    return std::tie(highestPair.first._id1, highestPair.first._id2, highestPair.second);
}

/**
 * @todo Implement function that will return two workers, which vacations are most intersected
 *
 * @param workerVacations - pairs of worker and his calendar
 * @return Max intersection of two workers and intersection days count
 */
std::tuple<worker_id, worker_id, days> getMaxIntersection(const std::unordered_map<worker_id, calendar>& workerVacations)
{
    std::unordered_map<worker_pair, size_t> vacationIntersections;

    for (auto& it : workerVacations)
    {
        const worker_id& id1 = it.first;

        std::for_each(workerVacations.begin(), workerVacations.end(), 
            [&](const std::pair<worker_id, calendar>& p)
            {
                if (is_same_worker(id1, p.first))
                    return;
                
                worker_pair workerPair {id1, p.first};
                vacationIntersections[workerPair] = getMaxIntersectionCount(it.second, p.second);
            }
        );
    }

    return findWorkerPairMaxIntersection(vacationIntersections);
}
