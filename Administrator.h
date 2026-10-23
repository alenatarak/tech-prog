#pragma once
#include <string>
#include "Conference.h"

class Administrator final : public Conference {
    std::string fullName_, position_, responsibility_;

   public:
    Administrator();
    Administrator(const std::string& name, const std::string& position,
                  const std::string& responsibility);
    Administrator(const Administrator& other);
    Administrator& operator=(const Administrator& other);
    ~Administrator() override;
    const std::string& getFullName() const;
    const std::string& getPosition() const;
    const std::string& getResponsibility() const;
    void setFullName(const std::string& value);
    void setPosition(const std::string& value);
    void setResponsibility(const std::string& value);
    int type() const override;
    Conference* clone() const override;
    void input() override;
    void print(std::ostream& out) const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
};
