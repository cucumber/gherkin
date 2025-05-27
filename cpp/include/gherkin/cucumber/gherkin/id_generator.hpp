#pragma once

#include <string>
#include <memory>

namespace cucumber::gherkin {

class id_generator_base
{
public:
    id_generator_base();

    virtual ~id_generator_base();

    virtual std::string next_id() = 0;
};

class id_generator : public id_generator_base
{
public:
    id_generator();
    virtual ~id_generator();

    std::string next_id() override;

private:
    std::size_t id_counter_ = 0;
};

using id_generator_ptr = std::shared_ptr<id_generator_base>;

template <typename... Args>
id_generator_ptr
new_id_generator(Args&&... args)
{ return std::make_shared<id_generator>(std::forward<Args>(args)...); }

}
