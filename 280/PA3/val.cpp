#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <iomanip>
#include "val.h"
using namespace std; 

// add op to this
Value Value::operator+(const Value& op) const{

}

// subtract op from this between floats or ints
Value Value::operator-(const Value& op) const{
    if(op.GetType() == VERR || this->GetType() == VERR){
        return Value();
    }
    if(op.GetType() == this->GetType()){
        if(op.GetType() == VINT){
            int ans = this->GetInt() - op.GetInt();
            return Value(ans);
        }else if(op.GetType() == VREAL){
            float ans = this->GetReal() - op.GetReal();
            return Value(ans);
        }
    }else if(op.GetType() == VINT && this->GetType() == VREAL){
        float ans = this->GetReal() - op.GetInt();
        return Value(ans);
    }else if(op.GetType() == VREAL && this->GetType() == VINT){
        float ans = this->GetInt() - op.GetReal();
        return Value(ans);
    }
    return Value();
}

// multiply this by op between floats or ints
Value Value::operator*(const Value& op) const{
    if(op.GetType() == VERR || this->GetType() == VERR){
        return Value();
    }
    if(op.GetType() == this->GetType()){
        if(op.GetType() == VINT){
            int ans = this->GetInt() * op.GetInt();
            return Value(ans);
        }else if(op.GetType() == VREAL){
            float ans = this->GetReal() * op.GetReal();
            return Value(ans);
        }
    }else if(op.GetType() == VINT && this->GetType() == VREAL){
        float ans = this->GetReal() * op.GetInt();
        return Value(ans);
    }else if(op.GetType() == VREAL && this->GetType() == VINT){
        float ans = this->GetInt() * op.GetReal();
        return Value(ans);
    }
    return Value();
}

// divide this by op
Value Value::operator/(const Value& op) const{

}

// this < op
Value Value::operator<(const Value& op) const{
    if(op.GetType() == VERR || this->GetType() == VERR){
        return Value();
    }
    if(op.GetType() == this->GetType()){
        if(op.GetType() == VBOOL){
            bool ans = this->GetBool() < op.GetBool();
            return ans;
        }/*else if(op.GetType() == VSTRING){
            bool ans = this->GetString() < op.GetString();
            return ans;
        }*/else if(op.GetType() == VINT){
            bool ans = this->GetInt() < op.GetInt();
            return ans;
        }else if(op.GetType() == VREAL){
            bool ans = this->GetReal() < op.GetReal();
            return ans;
        } 
    }else if(op.GetType() == VINT && this->GetType() == VREAL){
        bool ans = this->GetReal() < op.GetInt();
        return Value(ans);
    }else if(op.GetType() == VREAL && this->GetType() == VINT){
        bool ans = this->GetInt() < op.GetReal();
        return Value(ans);
    }
    return Value();
}

// AND between two bools
Value Value::operator&&(const Value& op) const{
    if(op.GetType() == VERR || this->GetType() == VERR){
        return Value();
    }
    if(op.GetType() == VBOOL && this->GetType() == VBOOL){
        bool ans = op.GetBool() && this->GetBool();
        return Value(ans);
    }
    return Value();
}