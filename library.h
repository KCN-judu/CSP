#ifndef CSP_LIBRARY_H
#define CSP_LIBRARY_H

/*
 * A CPP-based COMMAND SIMULATE PLATFORM
 * Use High-level programming language to express and test your thoughts
  ____ ____  ____
 / ___/ ___||  _ \
| |   \___ \| |_) |
| |___ ___) |  __/
 \____|____/|_|
 * Developed by KCN_JuDu
 * July 31st 2022
 * */

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>


namespace CSP{

    struct position{
        int x,
            y,
            z;
        position operator+(const position &a)const{
            return {
                x + a.x,
                y + a.y,
                z + a.z
            };
        }
    };

    struct offset{
        int x,
            y,
            z;
    };

    struct effect{
        std::string identifier;
        unsigned char level;
        int duration;
    };

    struct object {
        std::string type;
        std::string name;
        std::map<std::string,int> scores;
        std::vector<std::string> tag;
        position pos;
        std::vector<effect> effect;
    };

    int toNumber(const std::string &str){
        int x(0),pos(0),e(str.size()),w(1);
        for(;pos<e;++pos){
            if(str[pos]=='-')w-=1;
            else x=(x<<3)+(x<<1)+(str[pos]&15);
        }
        return x*w;
    }

    void ScoreboardOperations(object obj_1, std::string identifier_1, std::string operation, object obj_2, std::string identifier_2){
        if(operation == "+=")obj_1.scores[identifier_1] += obj_2.scores[identifier_2];
        else if(operation == "-=")obj_1.scores[identifier_1] -= obj_2.scores[identifier_2];
        else if(operation == "*=")obj_1.scores[identifier_1] *= obj_2.scores[identifier_2];
        else if(operation == "/=")obj_1.scores[identifier_1] /= obj_2.scores[identifier_2];
        else if(operation == "%=")obj_1.scores[identifier_1] %= obj_2.scores[identifier_2];
        else if(operation == "<")obj_1.scores[identifier_1] = obj_1.scores[identifier_1] < obj_2.scores[identifier_2] ? obj_1.scores[identifier_1] : obj_2.scores[identifier_2];
        else if(operation == ">")obj_1.scores[identifier_1] = obj_1.scores[identifier_1] > obj_2.scores[identifier_2] ? obj_1.scores[identifier_1] : obj_2.scores[identifier_2];
        else if(operation == "=")obj_1.scores[identifier_1] = obj_2.scores[identifier_2];
        else if(operation == "><")std::swap(obj_1.scores[identifier_1] , obj_2.scores[identifier_2]);
    }

    int FindTag (std::string tag, std::vector<std::string> tags){
        std::vector<std::string>::iterator it;
        it = find(tags.begin(), tags.end(), tag);
        if (it != tags.end())return it - tags.begin();
        else return -1;
    }

    bool TagRemove(object obj, std::string tag){
        int target = FindTag(tag,obj.tag);
        if(target == -1)return false;
        std::swap(obj.tag[target],obj.tag[tag.end() - tag.begin() - 1]);
        tag.pop_back();
        return true;
    }

    bool TagAdd(object obj, std::string tag){
        int target = FindTag(tag,obj.tag);
        if(target != -1)return false;
        obj.tag.push_back(tag);
        return true;
    }

    void tp(object obj, int x, int y, int z){
        position pos = {x, y, z};
        obj.pos = pos;
    }

    void tp(object obj, std::string dx, std::string dy, std::string dz){
        if(dx == "~")dx += "0";
        if(dy == "~")dy += "0";
        if(dz == "~")dz += "0";
        if(dx.find('~') == 4294967295){
            obj.pos.x = toNumber(dx);
            dx = "~0";
        }
        if(dy.find('~') == 4294967295){
            obj.pos.y = toNumber(dy);
            dy = "~0";
        }
        if(dz.find('~') == 4294967295){
            obj.pos.z = toNumber(dz);
            dz = "~0";
        }
        dx = dx.substr(1, dx.length() - 1);
        dy = dy.substr(1, dy.length() - 1);
        dz = dz.substr(1, dz.length() - 1);
        int  x, y, z;
        x = toNumber(dx);
        y = toNumber(dy);
        z = toNumber(dz);
        position offset = {x, y, z};
        obj.pos = obj.pos + offset;
    }

    std::vector<object> selector(){

    }
}




#endif //CSP_LIBRARY_H
