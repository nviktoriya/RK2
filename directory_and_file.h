#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Data
{
public:
    explicit Data(std::string name)
        : name_(std::move(name))
    {}
    virtual ~Data() = default;
    
    virtual std::uint64_t CalculateSize() const = 0;

    // These two functions (AddData, RemoveData) are only for Directory.
    // I add them into a common base class of both File and Directory
    //   even though they must not be called from File.
    // It is for getting extensibility and transparancy instead of type safety.
    virtual Data* AddData(std::unique_ptr<Data>&& data)
    {
        (void) data;
        throw std::logic_error("AddData() is not supported operation.");
    }
    virtual bool RemoveData(Data* dataPtr)
    {
        (void) dataPtr;
        throw std::logic_error("RemoveData() is not supported operation.");
    }

    std::string Name() const { return name_; }

private:
    std::string name_;
};

class Directory : public Data
{
public:
    explicit Directory(const std::string& name)
        : Data(name)
    {}

    std::uint64_t CalculateSize() const override
    {
        std::uint64_t size = 0u;
        for (auto const& data : dataList_)
            size += data->CalculateSize();
        return size;
    }

    Data* AddData(std::unique_ptr<Data>&& data) override
    {
        dataList_.push_back(std::move(data));
        return dataList_.back().get();
    }

    bool RemoveData(Data* dataPtr) override
    {
        auto dataIter = std::find_if(
            std::begin(dataList_),
            std::end(dataList_), 
            [dataPtr](auto const& data) -> bool
            {
                return data.get() == dataPtr;
            });

        if (dataIter == std::end(dataList_))
            return false;

        dataList_.erase(dataIter);
        return true;
    }

private:
    std::vector<std::unique_ptr<Data>> dataList_;
};

class File : public Data
{
public:
    File(std::string const& name, std::uint64_t size)
        : Data(name), size_(size)
    {}

    std::uint64_t CalculateSize() const override { return size_; }

private:
    std::uint64_t size_;
};

void PrintSize(Data const& data)
{
    std::cout << "Size of '" << data.Name() << "' = " << data.CalculateSize() << std::endl;
}

void RemoveData(Data& dir, Data* data)
{
    auto dataName = data->Name();
    bool success = dir.RemoveData(data);
    data = nullptr;

    if (success)
        std::cout << "Remove '" << dataName << "' from '" << dir.Name() << "'" << std::endl;
    else
        std::cout << "Fail to remove '" << dataName << "' from '" << dir.Name() << "'" << std::endl;
}

