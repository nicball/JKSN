#include <cmath>
#include "jksn.hpp"

namespace JKSN {

struct JKSNEncoderImpl {
};

struct JKSNDecoderImpl {
};

JKSNError::JKSNError(const char *reason) noexcept {
    this->reason = reason;
}

const char *JKSNError::what() const noexcept {
    return this->reason;
}

JKSNObject::JKSNObject() {
    this->data_type = JKSN_UNDEFINED;
}

JKSNObject::JKSNObject(bool data) {
    this->data_type = JKSN_BOOL;
    this->data_bool = data;
}

JKSNObject::JKSNObject(int64_t data) {
    this->data_type = JKSN_INT;
    this->data_int = data;
}

JKSNObject::JKSNObject(float data) {
    this->data_type = JKSN_FLOAT;
    this->data_float = data;
}

JKSNObject::JKSNObject(double data) {
    this->data_type = JKSN_DOUBLE;
    this->data_double = data;
}

JKSNObject::JKSNObject(long double data) {
    this->data_type = JKSN_LONG_DOUBLE;
    this->data_long_double = data;
}

JKSNObject::JKSNObject(std::shared_ptr<std::string> data, bool isblob) {
    this->data_type = isblob ? JKSN_BLOB : JKSN_STRING;
    this->data_string = data;
}

JKSNObject::JKSNObject(std::shared_ptr<std::vector<JKSNObject>> data) {
    this->data_type = JKSN_ARRAY;
    this->data_array = data;
}

JKSNObject::JKSNObject(std::shared_ptr<std::map<JKSNObject, JKSNObject>> data) {
    this->data_type = JKSN_OBJECT;
    this->data_object = data;
}

JKSNObject::~JKSNObject() {
    delete this;
}

jksn_data_type JKSNObject::getType() const {
    return this->data_type;
}

bool JKSNObject::toBool() const {
    switch(this->getType()) {
    case JKSN_UNDEFINED:
    case JKSN_NULL:
    case JKSN_UNSPECIFIED:
        return false;
    case JKSN_BOOL:
        return this->data_bool;
    case JKSN_INT:
        return this->data_int != 0;
    case JKSN_FLOAT:
        return this->data_float != 0.0f;
    case JKSN_DOUBLE:
        return this->data_double != 0.0;
    case JKSN_LONG_DOUBLE:
        return this->data_long_double != 0.0L;
    case JKSN_STRING:
    case JKSN_BLOB:
        return !this->data_string->empty();
    default:
        return true;
    }
}

int64_t JKSNObject::toInt() const {
    switch(this->getType()) {
    case JKSN_INT:
        return this->data_int;
    case JKSN_FLOAT:
        return int64_t(this->data_float);
    case JKSN_DOUBLE:
        return int64_t(this->data_double);
    case JKSN_LONG_DOUBLE:
        return int64_t(this->data_long_double);
    default:
        return 0;
    }
}

float JKSNObject::toFloat() const {
    switch(this->getType()) {
    case JKSN_INT:
        return float(this->data_int);
    case JKSN_FLOAT:
        return this->data_float;
    case JKSN_DOUBLE:
        return float(this->data_double);
    case JKSN_LONG_DOUBLE:
        return float(this->data_long_double);
    default:
        return NAN;
    }
}

double JKSNObject::toDouble() const {
    switch(this->getType()) {
    case JKSN_INT:
        return double(this->data_int);
    case JKSN_FLOAT:
        return double(this->data_float);
    case JKSN_DOUBLE:
        return this->data_double;
    case JKSN_LONG_DOUBLE:
        return double(this->data_long_double);
    default:
        return NAN;
    }
}

long double JKSNObject::toLongDouble() const {
    switch(this->getType()) {
    case JKSN_INT:
        return (long double) this->data_int;
    case JKSN_FLOAT:
        return (long double) this->data_float;
    case JKSN_DOUBLE:
        return (long double) this->data_double;
    case JKSN_LONG_DOUBLE:
        return this->data_long_double;
    default:
        return NAN;
    }
}

}
