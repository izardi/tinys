#ifndef _INI_PARSER__
#define _INI_PARSER__

#include <fstream>
#include <string>
#include <map>
#include <cstring>
#include <cstdio>
#include <sstream>

using std::string;
using std::ofstream;

namespace tinys{
namespace utility{

class Value {
public:

    Value() : m_value("") {}

    template <typename T>
    Value(const T& val) { *this = val; }

    template <typename T>
    Value& operator = (T& val) {
        if (typeid(val) == typeid(bool)) 
            m_value = (val ? "true" : "false");
        else if (typeid(val) == typeid(int) ||
            typeid(val) == typeid(double))
            m_value = to_string(val);
        else if (typeid(val) == typeid(string))
            m_value = val;
        return *this;
    }

    operator bool() {return m_value[0] == 't' ? true : false;}

    operator int() {return stoi(m_value);}

    operator double() {return stod(m_value);}

    operator string() const {return m_value;}
    
    const string& getV() const { return m_value; }

    ~Value(){};

private:
    string m_value;
};


class Ini {
    using Section = std::map<string, Value>;
    friend Value;
    
public:
    Ini() {};

    Ini(const string &filename) {
        load(filename);
    }

    ~Ini() {}
    
    bool load(const string &filename) {
        m_ini.clear();
        m_filename = filename;
        
        std::ifstream ifs(m_filename);
        if (ifs.fail()) {
            printf("loading file error: %s is not found.\n", m_filename.c_str());
            return false;
        }

        string linebuf;
        string sname;
        while (std::getline(ifs, linebuf)) {
            trim(linebuf);
            int pos;

            if ('[' == linebuf[0]) {
                pos = linebuf.find_first_of(']');
                linebuf[0] = ' '; linebuf[pos] = ' ';
                trim(linebuf);
                m_ini[linebuf];
                sname = linebuf;
            } else if ('#' == linebuf[0]) {continue;}
            else { // k - v
                pos = linebuf.find_first_of('=');
                if (pos > 0) {
                    string key = linebuf.substr(0, pos);
                    trim(key);
                    string value = linebuf.substr(pos+1);
                    trim(value);
                    
                    if (m_ini.find(sname) == m_ini.end()) {
                        printf("section %s: not found.\n", sname.c_str());
                        return false;
                    }

                    m_ini[sname][key] = value;
                }
            }
        }
        ifs.close();
        return true;
    }

    void save(const string &filename) {
        FILE *fp = fopen(filename.c_str(), "w+");
        if (fp == nullptr) perror("fopen");
        show(fp);
        fclose(fp);
    }

    void show(FILE *stream = stdout) const {
        std::map<string, Section>::const_iterator it;

        for (it = m_ini.begin(); it != m_ini.end(); ++it) {
            fprintf(stream, "[%s]\n", it->first.c_str());

            Section::const_iterator iter;
            for (iter = it->second.begin(); iter != it->second.end(); ++iter)
                fprintf(stream, "%s = %s\n", iter->first.c_str(), iter->second.getV().c_str());
        }
    }

    void clear() { m_ini.clear(); }
    
    Value& get(const string& section, const string& key) {
        return m_ini[section][key];
    }
    
    void set(const string&section, const string& key, bool val) {
        m_ini[section][key] = val; 
    }
    
    void set(const string&section, const string& key, int val) {
        m_ini[section][key] = val;
    }
    
    void set(const string&section, const string& key, double val) {
        m_ini[section][key] = val;
    }

    void set(const string&section, const string& key, const string& val) {
        m_ini[section][key] = val;    
    }

    bool has(const string& section) {
        return (m_ini.find(section) != m_ini.end()); 
    }

    bool has(const string& section, const string& key) {
        std::map<string, Section>::const_iterator it = m_ini.find(section);
        if (it != m_ini.end())
            return (it->second.find(key) != it->second.end());
        return false;
    }
    
    void remove(const string& section) {
        std::map<string, Section>::const_iterator it = m_ini.find(section);
        if (it != m_ini.end()) m_ini.erase(it);
    }

    void remove(const string& section, const string& key) {
        std::map<string, Section>::iterator it = m_ini.find(section);
        if (it != m_ini.end()) {
            Section::const_iterator iter = it->second.find(key);            
            if (iter != it->second.end())
                it->second.erase(iter);
        }
    }
    
    Section& operator[](const string& key) {
        return m_ini[key];
    }

private:
    void trim(string &str) {
        str.erase(0, str.find_first_not_of(" \r\n"));
        str.erase(str.find_last_not_of(" \r\n")+1);
    }

    string m_filename;
    std::map<string, Section> m_ini;

};


}
}

#endif