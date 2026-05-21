#pragma once

#include <string>
#include <vector>

/// Bonus unit converter: dynamic registration with meter hub (Item-free, standalone).
class DecayingUnit {
public:
    DecayingUnit();

    struct ConvertAllEntry {
        std::string unit;
        double value{0.0};
    };

    void registerUnit(const std::string& name, double meters_per_unit);
    double convert(const std::string& from_unit, double value, const std::string& to_unit) const;
    std::vector<ConvertAllEntry> convertAll(const std::string& from_unit, double value) const;

private:
    struct UnitEntry {
        std::string symbol;
        double meters_per_unit{0.0};
    };

    std::vector<UnitEntry> units_;
};
