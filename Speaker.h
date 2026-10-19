#pragma once
#include <string>
#include "Base.h"

class Speaker final : public Base {
    std::string fullName_, organization_, report_, annotation_;

   public:
    Speaker();
    Speaker(const std::string& name, const std::string& organization,
            const std::string& report, const std::string& annotation);
    Speaker(const Speaker& other);
    Speaker& operator=(const Speaker& other);
    ~Speaker() override;
    const std::string& getFullName() const;
    const std::string& getOrganization() const;
    const std::string& getReport() const;
    const std::string& getAnnotation() const;
    void setFullName(const std::string& value);
    void setOrganization(const std::string& value);
    void setReport(const std::string& value);
    void setAnnotation(const std::string& value);
    int type() const override;
    Base* clone() const override;
    void input() override;
    void print(std::ostream& out) const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
};
