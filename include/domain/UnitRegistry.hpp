#pragma once

#include "domain/UnitDefinition.hpp"

#include <optional>
#include <string>
#include <vector>

namespace domain {

class UnitRegistry {
public:
    static UnitRegistry bootstrapDefault();

    bool registerUnit(const std::string& symbol, double meters_per_unit);
    std::optional<UnitDefinition> find(const std::string& symbol) const;
    const std::vector<UnitDefinition>& units() const { return units_; }
    std::size_t size() const { return units_.size(); }
    void clear();
    void loadFromDefinitions(const std::vector<UnitDefinition>& definitions);

private:
    std::vector<UnitDefinition> units_;
};

}  // namespace domain
