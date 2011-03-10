// Simple tiny useless wrapper for command-line arguments
// Never use this if you hate STL, it's very slow and eats much memory!
// By Alexander Ptakhin, 2010. Public Domain.
#ifndef PROGOPT_H
#define PROGOPT_H

#include <vector>
#include <string>
#include <map>
#include <locale>

namespace progopt 
{
    typedef std::string String;

    class Value
    {
    protected:

        String _value;

    protected:

        template <typename T>
        T get() const
        {
            T v;
            std::istringstream stream(_value);
            stream >> v;
            return v;
        }

    public:

        Value(const String& s) : _value(s) {}

        String as_string() const { return _value; }
    };

    bool operator == (const Value& val, const String& str)
    {
        return val.as_string() == str;
    }

    class Values
    {
    public:

        bool is_single() const { return _values.size() == 1; }

        void add(const Value& v)
        {
            _values.push_back(v);
        }

        Value& operator [] (size_t i)
        {
            return _values[i];
        }

        const Value& operator [] (size_t i) const
        {
            return _values[i];
        }

        size_t count() const { return _values.size(); }

    protected:
        std::vector<Value> _values;
    };

    /**
        Wrapper
     */
    class Args
    {
    protected:
        std::vector<Value> _num_args;

        typedef std::map<String, Values> KeyValues;

        KeyValues _key_args;

        const static Values Empty;

    public:
        /// The only constructor
        Args(int argc, char* argv[])
        {
            std::vector<String> cmds;

            for (int i = 1; i < argc; ++i)
                cmds.push_back(argv[i]);

            cmds.push_back("");// For more clear code parsing

            put_parsed(cmds);
        }

        /// Quintity of numered arguments.
        size_t num_args() const { return _num_args.size(); }

        /// Count of numered args
        const Value& num_arg(size_t i) const { return _num_args[i]; }

        /// Checks numered arg and return pointer, if exists.
        const Value* has_num_arg(size_t i) const 
        {
            if (i < _num_args.size())
                return &_num_args[i]; 
            return nullptr;
        }

        /// Returns arg by key.
        const Values& key_arg(const String& key) const 
        { 
            KeyValues::const_iterator i = _key_args.find(key);
            if (i != _key_args.end())
                return i->second; 
            return Empty;
        }

        /// Check existence of argument by key.
        bool has_key_arg(const String& key) const 
        {
            KeyValues::const_iterator i = _key_args.find(key);
            return i != _key_args.end();
        }

        /// Returns single value of argument by key.
        const Value* has_key_arg_val(const String& key) const 
        {
            KeyValues::const_iterator i = _key_args.find(key);
            if (i != _key_args.end() && i->second.is_single())
                return &i->second[0];
            return nullptr;
        }

        /// Returns values array (if has) of argument by key.
        const Values* has_key_arg_arr(const String& key) const 
        {
            KeyValues::const_iterator i = _key_args.find(key);
            if (i != _key_args.end())
                return &i->second;
            return nullptr;
        }

    protected:

        String normalise_key(const String& t)
        {
            size_t start_trim = 0;
            for (; start_trim < t.size(); ++start_trim)
            {
                if (t[start_trim] != '-')
                    break;
            }

            return t.substr(start_trim, t.size() - start_trim);
        }

        void put_parsed(const std::vector<String>& cmds)
        {
            enum State
            {
                S_NUM,
                S_KEYS
            };

            State g = S_NUM;
            size_t i = 0;

            // While we haven't meet `-`
            for (; i < cmds.size() && cmds[i].find("-") != 0; ++i)
                _num_args.push_back(Value(cmds[i]));

            // While true on constant buffer:)
            for (; i < cmds.size(); )
            {
                String key = normalise_key(cmds[i]);
                Values values;
 
                for (++i; i < cmds.size() && cmds[i].find("-") != 0 && cmds[i] != ""; ++i)
                    values.add(Value(cmds[i]));

                _key_args.insert(std::make_pair(key, values));
            }
        }
        
    protected:

    }; // class Parser

} // namespace progopt

#endif // #ifndef PROGOPT_H
