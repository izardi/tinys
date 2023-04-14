#ifndef _JSON_H_
#define _JSON_H_

#include <vector>
#include <map>
#include <string>
using std::string;
using std::vector;
using std::map;

namespace tinys {
namespace utility{


class Json {
public:

    enum Type {
        json_null = 0,
        json_bool,
        json_int,
        json_double,
        json_string,
        json_array,
        json_object
    };

    Json(Type typ = json_null) : m_type(typ){}
    Json(bool val) : m_type(json_bool) { m_json.m_bool = val; }
    Json(int val) : m_type(json_int) { m_json.m_int = val; }
    Json(double val);
    Json(const char *val);
    Json(const string& val);
    ~Json();

    Type type() const;

    bool isNull() const;

    bool isBool() const;

    bool isInt() const;

    bool isDouble() const;

    bool isArray() const;

    bool isObject() const;

    bool asBool() const;

    int asInt() const;

    double asDouble() const;

    string asString() const;

    void copy(const Json& other);

    size_t size() const;

    bool empty() const;

    void clear();

    bool remove(int idx);
    
    bool remove(const char* key);

    bool remove(const string& key);

    bool has(int idx);

    bool has(const char* key);

    bool has(const string& key);

    const Json& get(int idx) const;

    const Json& get(const char* key) const;

    const Json& get(const string& key) const;

    void set(const Json& oth);

    void set(bool val);

    void set(double val);

    void set(const string& val);

    void set(const char* val);

    Json& operator = (const Json& oth);

    Json& operator = (bool val);

    Json& operator = (double val);

    Json& operator = (int val);

    Json& operator = (const char* val);

    Json& operator = (const string& val);

    bool operator == (const Json &oth);
    bool operator == (bool val);
    bool operator == (int val);
    bool operator == (double val);
    bool operator == (const string& val);
    bool operator == (const char *val);

    bool operator != (const Json &oth);
    bool operator != (bool val);
    bool operator != (int val);
    bool operator != (double val);
    bool operator != (const string& val);
    bool operator != (const char* val);

    Json& operator [] (int idx);

    const Json& operator [] (int idx) const;

    Json& operator [] (const char *key);

    const Json& operator [] (const char *key) const;

    Json& operator [] (const string& key);

    const Json& operator [] (const string& key) const;

    operator bool();

    operator int();

    operator double();

    operator string();

    operator string() const;

    static Json const & null();

    void parse(const string & str);

    string toString() const;

    using iterator = std::vector<Json>::iterator;
    using citerator = std::vector<Json>::const_iterator;

    iterator begin() {
    }

private:

    Type m_type;

    union ujson {
        int m_int;
        double m_double;
        bool m_bool;
        string m_string;
        vector<Json> m_array;
        map<string, Json> m_object;
    };
    ujson m_json;
};


}
}

#endif
