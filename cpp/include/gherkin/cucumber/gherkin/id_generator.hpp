#ifndef CUCUMBER_GHERKIN_ID_GENERATOR_HPP
#define CUCUMBER_GHERKIN_ID_GENERATOR_HPP

#include <memory>
#include <string>

namespace cucumber::gherkin
{

    class IdGeneratorBase
    {
    public:
        IdGeneratorBase() = default;

        virtual ~IdGeneratorBase() = default;
        IdGeneratorBase(const IdGeneratorBase&) = delete;
        IdGeneratorBase& operator=(const IdGeneratorBase&) = delete;
        IdGeneratorBase(IdGeneratorBase&&) = delete;
        IdGeneratorBase& operator=(IdGeneratorBase&&) = delete;

        virtual std::string NextId() = 0;
    };

    class IdGenerator : public IdGeneratorBase
    {
    public:
        IdGenerator() = default;
        ~IdGenerator() override = default;
        IdGenerator(const IdGenerator&) = delete;
        IdGenerator& operator=(const IdGenerator&) = delete;
        IdGenerator(IdGenerator&&) = delete;
        IdGenerator& operator=(IdGenerator&&) = delete;

        std::string NextId() override;

    private:
        std::size_t idCounter = 0;
    };

    using IdGeneratorPtr = std::shared_ptr<IdGeneratorBase>;

    template<typename... Args>
    IdGeneratorPtr NewIdGenerator(Args&&... args)
    {
        return std::make_shared<IdGenerator>(std::forward<Args>(args)...);
    }

}

#endif
