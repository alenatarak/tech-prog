#pragma once
#include <string>
#include "Conference.h"

class ProgramItem final : public Conference {
    std::string day_, time_, title_;

   public:
    ProgramItem();
    ProgramItem(const std::string& day, const std::string& time,
                const std::string& title);
    ProgramItem(const ProgramItem& other);
    ProgramItem& operator=(const ProgramItem& other);
    ~ProgramItem() override;
    const std::string& getDay() const;
    const std::string& getTime() const;
    const std::string& getTitle() const;
    void setDay(const std::string& value);
    void setTime(const std::string& value);
    void setTitle(const std::string& value);
    int type() const override;
    Conference* clone() const override;
    void input() override;
    void print(std::ostream& out) const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
};
