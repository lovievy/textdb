#include "db.h"

DB::DB(const std::string& filename) {
    file_ = std::make_unique<std::fstream>(filename, std::ios::out | std::ios::in | std::ios::app | std::ios::binary | std::ios::ate);
}

void DB::Put(const std::string& key, const std::string& value) const {
    file_->seekp(0, file_->end);

    const std::string offset = EncodeUvarint(file_->tellp());
    const std::string key_length = EncodeUvarint(key.size());
    const std::string value_length = EncodeUvarint(value.size());

    WriteString({key_length, key, value_length, value, kDBMarker, offset});
}

std::string DB::Get(const std::string& _key) const {
    file_->seekg(0, file_->end);
    file_->seekg(-1, file_->cur);

    std::string key, value;
    while (key != _key) {
        while (static_cast<int>(static_cast<char>(file_->peek())) != static_cast<int>(kDBMarker.c_str()[0])) {
            file_->seekg(-1, file_->cur);
        }

        file_->seekg(1, file_->cur);

        uint64_t offset = ReadUvarint();
        file_->seekg(offset, file_->beg);

        uint64_t key_length = ReadUvarint();
        ReadString(key, key_length);

        if (key != _key && offset == 0) {
            return "";
        }

        if (key != _key) {
            file_->seekg(offset, file_->beg);
            continue;
        }

        uint64_t value_length = ReadUvarint();
        ReadString(value, value_length);
    }

    return value;
}

void DB::Close() {
    file_->close();
    file_.reset();
    return;
}

uint64_t DB::ReadUvarint() const {
    uint64_t uvarint = 0, s = 0;
    char c;
    while (file_->read(&c, 1)) {
        uvarint |= (c & 0x7f) << s;
        if ((c & 0x80) == 0) {
            break;
        }
        s += 7;
    }
    return uvarint;
}

void DB::ReadString(std::string& str, const uint64_t length) const {
    str.resize(length);
    file_->read(&str[0], length);
    return;
}

void DB::WriteString(const std::string& str) const {
    file_->write(str.c_str(), str.size());
    return;
}

void DB::WriteString(const std::initializer_list<std::string>& strs) const {
    for (const auto& str : strs) {
        if (str == kDBMarker) {
            WriteMarker();
        } else {
            WriteString(str);
        }
    }
    return;
}

void DB::WriteMarker() const {
    file_->write(kDBMarker.c_str(), 1);
    return;
}

std::string EncodeUvarint(uint64_t value) {
    if (value == 0) {
        return std::string("\x00", 1);
    }

    std::string result;
    while (value >= 0x80) {
        result.push_back(0x80 | (value & 0x7f));
        value >>= 7;
    }
    result.push_back(value);
    return result;
}