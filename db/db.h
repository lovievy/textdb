#pragma once

#include <fstream>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <string>

namespace textdb {

const std::string kDBMarker("\xFF");

class DB {
public:
    static std::shared_ptr<DB> Open(const std::string& filename);

    explicit DB(const std::string& filename);

    void Put(const std::string& key, const std::string& value) const;

    std::string Get(const std::string& _key) const;

    void Close();

private:
    std::unique_ptr<std::fstream> file_;

    uint64_t ReadUvarint() const;
    void ReadString(std::string& dst, const uint64_t length) const;

    void WriteString(const std::string& str) const;
    void WriteString(const std::initializer_list<std::string>& strs) const;
    void WriteMarker() const;
};

std::string EncodeUvarint(uint64_t value);

};  // namespace textdb