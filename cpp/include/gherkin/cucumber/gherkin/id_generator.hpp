#ifndef CUCUMBER_GHERKIN_ID_GENERATOR_HPP
#define CUCUMBER_GHERKIN_ID_GENERATOR_HPP

#include <memory>
#include <string>

namespace cucumber::gherkin
{

    class IdGeneratorBase
    {
    public:
        IdGeneratorBase();

        virtual ~IdGeneratorBase();

        virtual std::string next_id() = 0;
    };

    class IdGenerator : public IdGeneratorBase
    {
    public:
        IdGenerator();
        virtual ~IdGenerator();

        std::string next_id() override;

    private:
        std::size_t id_counter_ = 0;
    };

    using id_generator_ptr = std::shared_ptr<IdGeneratorBase>;

    template<typename... Args>
    id_generator_ptr new_id_generator(Args&&... args)
    {
        return std::make_shared<IdGenerator>(std::forward<Args>(args)...);
    }

}

#endif
