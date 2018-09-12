/*
 * LibreTuner
 * Copyright (C) 2018 Altenius
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TABLEGROUP_H
#define TABLEGROUP_H

#include "definitions/definition.h"
#include "rom.h"

#include <vector>
#include <memory>
#include <gsl/span>

class Table;


/**
 * Handles a group of tables
 */
class TableGroup {
public:
    explicit TableGroup(const std::shared_ptr<Rom> &base);

    size_t count() const { return tables_.size(); }

    /* Returns a table from a table id. If create is true and
     * a table does not exist, creates a new table
     * from the ROM data. Returns nullptr if create is false
     * and the table does not exist. */
    Table *get(size_t idx, bool create = true);

    /* Creates a new table from data. May throw exception. */
    void set(size_t idx, gsl::span<const uint8_t> data);

    /* Applies table modifications to rom data */
    void apply(gsl::span<uint8_t> data);

private:
    std::shared_ptr<Rom> base_;

    std::vector<std::unique_ptr<Table>> tables_;
};
typedef std::shared_ptr<TableGroup> TableGroupPtr;

#endif // TABLEGROUP_H
