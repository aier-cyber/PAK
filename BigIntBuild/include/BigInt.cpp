#include "BigInt.h"

void BigInt::Polar_Changer(int key){
    if (key == 0){
        if (-(*this) == BigInt(0)){
            this->isNeg = 0;
        }
    }
    else{
        if (*this == BigInt(0)){
            this->_bigint.at(0) = 1;
            this->isNeg = 1;
        }
    }
}

char* BigInt::getBigInt() const{
    char* mimic;
    int i;
    int vai = this->_bigint.size();
    if (this->isNeg){
        mimic = new char[vai+2];
        mimic[0] = '-';
        for (i = 1; i < vai+1; i++){
            mimic[i] = this->_bigint.at(vai-i)+48;
        }
        mimic[vai+1] = '\0';
    }
    else{
        mimic = new char[vai+1];
        for (i = 0; i < vai; i++){
            mimic[i] = this->_bigint.at(vai-i-1)+48;
        }
        mimic[vai] = '\0';
    }
    return mimic;
}

BigInt BigInt::getBin() const{
    BigInt m_copy = *this;
    std::vector<char> Binary_interpretation;
    m_copy.isNeg = 0;
    BigInt curr_value = 1;
    int curr_power = 0;
    while (1){
        if (curr_value*BigInt(2) > m_copy){
            break;
        }
        curr_value *= 2;
        curr_power += 1;
    }
    Binary_interpretation.resize(curr_power+1, 0);
    while(curr_power != -1){
        if (m_copy >= curr_value){
            m_copy -= curr_value;
            Binary_interpretation.at(curr_power) = 1;
            curr_value /= 2;
            curr_power -= 1;
        }
        else{
            curr_value /= 2;
            curr_power -= 1;
        }
    }
    m_copy._bigint = Binary_interpretation;
    m_copy.isNeg = this->isNeg;
    return m_copy;
}

//**************
//**************
//**************

BigInt::BigInt(){
    this->isNeg = 0;
}

BigInt::BigInt(int x){
    if (x == 0){
        this->isNeg = 0;
        this->_bigint.push_back(0);
    }
    else{
    if (x < 0){
        this->isNeg = 1;
        x = -x;
    }
    else{
        this->isNeg = 0;
    }
    int i = 0;
    while(x > 0){
        this->_bigint.push_back(x%10);
        x /= 10;
        i++;
    }
    }
}

BigInt::BigInt(long long x){
    if (x == 0){
        this->isNeg = 0;
        this->_bigint.push_back(0);
    }
    else{
    if (x < 0){
        this->isNeg = 1;
        x = -x;
    }
    else{
        this->isNeg = 0;
    }
    int i = 0;
    while(x > 0){
        this->_bigint.push_back(x%10);
        x /= 10;
        i++;
    }
    }
}

BigInt::BigInt(std::string bi){ // бросать исключение std::invalid_argument при ошибке
    int i;
    if (bi[0] == '-'){
        for(i = 1; i < int(bi.length()); i++){
            if (isdigit(bi[i])){}
            else{ break; }
        }
        if ((i == int(bi.length())) && (bi[1] != '0')){
            this->isNeg = 1;
            for(i = 1; i < int(bi.length()); i++){
                this->_bigint.push_back(bi[bi.length()-i]-48);
            }
        }
        else{
            throw std::invalid_argument("Error: non-digit value in string parameter!");
        }

    }
    else{
        for(i = 0; i < bi.length(); i++){
                if (isdigit(bi[i])){}
                else{ break; }
        }
        if ((i == bi.length()) && (bi[0] != '0')){
                this->isNeg = 0;
                for(i = 0; i < bi.length(); i++){
                    this->_bigint.push_back(bi[bi.length()-i-1]-48);
                }
        }
        else{
            throw std::invalid_argument("Error: non-digit value in string parameter!");
        }
    }
}

BigInt::BigInt(const BigInt& i){
    this->_bigint = i._bigint;
    this->isNeg = i.isNeg;
}

BigInt::~BigInt(){
}


BigInt& BigInt::operator=(const BigInt& i){
    this->isNeg = i.isNeg;
    this->_bigint = i._bigint;
    return *this;
}

BigInt& BigInt::operator++(){
    if (this->isNeg){
        this->_bigint.at(0) -= 1;
        int i = 0;
        while(this->_bigint.at(i) == (-1)){
            this->_bigint.at(i) = 9;
            this->_bigint.at(i+1) -= 1;
            ++i;
        }
        this->Polar_Changer(0);
        if ((this->_bigint.at(this->_bigint.size() - 1) == 0) && (*this != BigInt(0))){
                this->_bigint.pop_back();
        }
    }
    else{
        this->_bigint.at(0) += 1;
        int i = 0;
        while(this->_bigint.at(i) == 10){
            if (i == this->_bigint.size() - 1){
                this->_bigint.push_back(1);
                this->_bigint.at(i) %= 10;
            }
            else{
                this->_bigint.at(i) %= 10;
                this->_bigint.at(i+1) += 1;
                ++i;
            }
        }
    }
    return *this;
}

const BigInt BigInt::operator++(int){
    BigInt m_copy = *this;
    ++*this;
    return m_copy;
}

BigInt& BigInt::operator--(){
    if (this->isNeg){
        this->_bigint.at(0) += 1;
        int i = 0;
        while(this->_bigint.at(i) == 10){
            if (i == this->_bigint.size() - 1){
                this->_bigint.push_back(1);
                this->_bigint.at(i) %= 10;
            }
            else{
                this->_bigint.at(i) %= 10;
                this->_bigint.at(i+1) += 1;
                ++i;
            }
        }
    }
    else{
        if (*this == BigInt(0)){
            Polar_Changer(1);
        }
        else{
            this->_bigint.at(0) -= 1;
            int i = 0;
            while(this->_bigint.at(i) == (-1)){
                this->_bigint.at(i) = 9;
                this->_bigint.at(i+1) -= 1;
                ++i;
            }
            if ((this->_bigint.at(this->_bigint.size() - 1) == 0) && (*this != BigInt(0))){
                    this->_bigint.pop_back();
            }
        }
    }
    return *this;
}

const BigInt BigInt::operator--(int){
    BigInt m_copy = *this;
    --*this;
    return m_copy;
}

BigInt BigInt::operator+() const{
    BigInt m_copy(*this);
    return m_copy;
}

BigInt BigInt::operator-() const{
    BigInt m_copy(*this);
    if (m_copy.isNeg){
        m_copy.isNeg = 0;
    }
    else{
        m_copy.isNeg = 1;
    }
    return m_copy;
}

bool BigInt::operator==(const BigInt& i) const{
    if ((this->_bigint.size() == i._bigint.size()) && (this->isNeg == i.isNeg)){
        int lent = this->_bigint.size();
        int c;
        for(c = 0; c < lent; c++){
            if (this->_bigint.at(c) == i._bigint.at(c)){
                continue;
            }
            else{
                return false;
                break;
            }
        }
        return true;
    }
    else{
        return false;
    }
}

bool BigInt::operator!=(const BigInt& i) const{
    if (*this == i){
        return false;
    }
    else{
        return true;
    }
}

bool BigInt::operator<(const BigInt& i) const{
    if (i.isNeg > this->isNeg){
        return false;
    }
    if (i.isNeg < this->isNeg){
        return true;
    }
    int lent = i._bigint.size();
    if (lent < this->_bigint.size()){
        if (i.isNeg == 1){
            return true;
        }
        else{
            return false;
        }
    }
    if (lent > this->_bigint.size()){
        if (i.isNeg == 1){
            return false;
        }
        else{
            return true;
        }
    }
    bool is_i_mod_bigger;
    int c;
    for (c = lent-1; c >= 0; c--){
        if (i._bigint.at(c) > this->_bigint.at(c)){
            is_i_mod_bigger = true;
            break;
        }
        if (i._bigint.at(c) < this->_bigint.at(c)){
            is_i_mod_bigger = false;
            break;
        }
    }
    if (c == (-1)){
        return false;
    }
    else{
        if (i.isNeg == 1){
            if(is_i_mod_bigger == true){
                return false;
            }
            else{
                return true;
            }
        }
        else{
            if(is_i_mod_bigger == true){
                return true;
            }
            else{
                return false;
            }
        }
    }
}

bool BigInt::operator>(const BigInt& i) const{
    if (i.isNeg > this->isNeg){
        return true;
    }
    if (i.isNeg < this->isNeg){
        return false;
    }
    int lent = i._bigint.size();
    if (lent < this->_bigint.size()){
        if (i.isNeg == 1){
            return false;
        }
        else{
            return true;
        }
    }
    if (lent > this->_bigint.size()){
        if (i.isNeg == 1){
            return true;
        }
        else{
            return false;
        }
    }
    bool is_i_mod_bigger;
    int c;
    for (c = lent-1; c >= 0; c--){
        if (i._bigint.at(c) > this->_bigint.at(c)){
            is_i_mod_bigger = true;
            break;
        }
        if (i._bigint.at(c) < this->_bigint.at(c)){
            is_i_mod_bigger = false;
            break;
        }
    }
    if (c == (-1)){
        return false;
    }
    else{
        if (i.isNeg == 1){
            if(is_i_mod_bigger == true){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            if(is_i_mod_bigger == true){
                return false;
            }
            else{
                return true;
            }
        }
    }
}

bool BigInt::operator<=(const BigInt& i) const{
    if (*this == i){
        return true;
    }
    else{
        return (*this < i);
    }
}

bool BigInt::operator>=(const BigInt& i) const{
    if (*this == i){
        return true;
    }
    else{
        return (*this > i);
    }
}

BigInt& BigInt::operator+=(const BigInt& i){
    if (this->isNeg == i.isNeg){
        int overflow = 0;
        int m_size;
        if (this->_bigint.size() > i._bigint.size()){
            m_size = this->_bigint.size();
        }
        else{
            m_size = i._bigint.size();
        }
        for(int c = 0; c < m_size; c++){
            int curr = 0;
            if (c < i._bigint.size()){
                curr += i._bigint.at(c);
            }
            curr += overflow;
            if (c < this->_bigint.size()){
                curr += this->_bigint.at(c);
                this->_bigint.at(c) = curr%10;
            }
            else{
                this->_bigint.push_back(curr%10);
            }
            overflow = curr/10;
        }
        if (overflow){
            this->_bigint.push_back(1);
        }
    }
    else{
        BigInt i_copy = i;
        if (this->isNeg == 1){
            if (*this >= (-i_copy)){
                i_copy -= (-*this);
                *this = i_copy;
            }
            else{
                *this -= (-i_copy);
            }
        }
        else{
            if (*this >= (-i_copy)){
                *this -= (-i_copy);
            }
            else{
                i_copy -= (-*this);
                *this = i_copy;
            }
        }
    }
    return *this;
}

BigInt& BigInt::operator-=(const BigInt& i){
    if (*this == i){
        *this = 0;
        return *this;
    }
    if (this->isNeg == i.isNeg){
        if (i.isNeg == 1){
            if (*this > i){
                BigInt i_copy = i;
                i_copy -= *this;
                *this = -(i_copy);
            }
            else{
                for (int c = 0; c < this->_bigint.size(); c++){
                    int curr = 0;
                    curr += this->_bigint.at(c);
                    if (c < i._bigint.size()){
                        curr -= i._bigint.at(c);
                    }
                    if (curr >= 0){
                        this->_bigint.at(c) = curr;
                    }
                    else{
                        this->_bigint.at(c) = curr + 10;
                        this->_bigint.at(c+1) -= 1;
                    }
                }
                int len = this->_bigint.size() - 1;
                while(this->_bigint.at(len) == 0){
                    this->_bigint.pop_back();
                    len--;
                }
            }
        }
        else{
            if (*this > i){
                for (int c = 0; c < this->_bigint.size(); c++){
                    int curr = 0;
                    curr += this->_bigint.at(c);
                    if (c < i._bigint.size()){
                        curr -= i._bigint.at(c);
                    }
                    if (curr >= 0){
                        this->_bigint.at(c) = curr;
                    }
                    else{
                        this->_bigint.at(c) = curr + 10;
                        this->_bigint.at(c+1) -= 1;
                    }
                }
                int len = this->_bigint.size() - 1;
                while(this->_bigint.at(len) == 0){
                    this->_bigint.pop_back();
                    len--;
                }
            }
            else{
                BigInt i_copy = i;
                i_copy -= *this;
                *this = -(i_copy);
            }
        }
    }
    else{
        *this += (-i);
    }
    return *this;
}

BigInt& BigInt::operator*=(const BigInt& i){
    if (this->isNeg == i.isNeg){
        this->isNeg = 0;
    }
    else{
        this->isNeg = 1;
    }
    BigInt mimic = *this;
    BigInt counter = i;
    counter.isNeg = 0;
    *this = 0;
    while (counter > BigInt(0)){
        *this += mimic;
        --counter;
    }
    this->Polar_Changer(0);
    return *this;
}

BigInt& BigInt::operator/=(const BigInt& i){
    if (i == BigInt(0)){
        throw std::invalid_argument("Error: division by zero!");
    }
    BigInt i_copy = i;
    i_copy.isNeg = 0;
    int polarity = this->isNeg;
    this->isNeg = 0;
    BigInt res = 0;
    while (*this >= i_copy){
        *this -= i_copy;
        res++;
    }
    *this = res;
    if (polarity == i.isNeg){
        this->isNeg = 0;
    }
    else{
        this->isNeg = 1;
    }
    this->Polar_Changer(0);
    return *this;
}

BigInt& BigInt::operator%=(const BigInt& i){
    if (i == BigInt(0)){
        throw std::invalid_argument("Error: division by zero!");
    }
    BigInt i_copy = i;
    i_copy.isNeg = 0;
    int polarity = this->isNeg;
    this->isNeg = 0;
    while (*this >= i_copy){
        *this -= i_copy;
    }
    this->isNeg = polarity;
    this->Polar_Changer(0);
    return *this;
}

BigInt operator+(const BigInt& a, const BigInt& b){
    BigInt ans = a;
    ans += b;
    return ans;
}

BigInt operator-(const BigInt& a, const BigInt& b){
    BigInt ans = a;
    ans -= b;
    return ans;
}

BigInt operator*(const BigInt& a, const BigInt& b){
    BigInt ans = a;
    ans *= b;
    return ans;
}

BigInt operator/(const BigInt& a, const BigInt& b){
    BigInt ans = a;
    ans /= b;
    return ans;
}

BigInt operator%(const BigInt& a, const BigInt& b){
    BigInt ans = a;
    ans %= b;
    return ans;
}

BigInt BigInt::operator~() const{
    BigInt m_copy = 0;
    BigInt bin = this->getBin();
    int spun = 1;
    for (int i = bin._bigint.size()-1; i > -1; i--){
        bin._bigint.at(i) = 1-bin._bigint.at(i);
        if (bin._bigint.at(i)){
            spun = 0;
        }
        if (spun){
            if ((bin._bigint.at(i) == 0) && (i != 0)){
                bin._bigint.pop_back();
            }
        }
    }
    bin.isNeg = 1-bin.isNeg;
// decryption
    BigInt curr_value = 1;
    for (int i = 0; i < bin._bigint.size(); i++){
        if (bin._bigint.at(i) == 1){
            m_copy += curr_value;
        }
        if (i != bin._bigint.size() - 1){
            curr_value *= 2;
        }
    }
    m_copy.isNeg = bin.isNeg;
    m_copy.Polar_Changer(0);
    return m_copy;
}

BigInt& BigInt::operator^=(const BigInt& a){
    BigInt m_copy = 0;
    std::vector<char> bin_ans;
    BigInt bin_one = this->getBin();
    BigInt bin_two = a.getBin();
    int len_m = std::max(bin_one._bigint.size(), bin_two._bigint.size());
    bin_ans.resize(len_m,0);
    int spun = 1;
    for(int i = len_m - 1; i > -1; i--){
        if (i > bin_two._bigint.size() - 1){
            bin_ans.at(i) = bin_one._bigint.at(i);
            if (bin_ans.at(i)){
                spun = 0;
            }
            if(spun){
                if ((bin_ans.at(i) == 0) && (i != 0)){
                    bin_ans.pop_back();
                }
            }
        }
        else{
            if (i > bin_one._bigint.size() - 1){
                bin_ans.at(i) = bin_two._bigint.at(i);
                if (bin_ans.at(i)){
                    spun = 0;
                }
                if(spun){
                    if ((bin_ans.at(i) == 0) && (i != 0)){
                        bin_ans.pop_back();
                    }
                }
            }
            else{
                if(bin_one._bigint.at(i)){
                    bin_ans.at(i) = 1-bin_two._bigint.at(i);
                }
                else{
                    bin_ans.at(i) = bin_two._bigint.at(i);
                }
                if (bin_ans.at(i)){
                    spun = 0;
                }
                if(spun){
                    if ((bin_ans.at(i) == 0) && (i != 0)){
                        bin_ans.pop_back();
                    }
                }
            }
        }
    }
// decryption
    BigInt curr_value = 1;
    bin_one._bigint = bin_ans;
    for (int i = 0; i < bin_ans.size(); i++){
        if (bin_ans.at(i) == 1){
            m_copy += curr_value;
        }
        if (i != bin_ans.size() - 1){
            curr_value *= 2;
        }
    }
    if (bin_one.isNeg){
        m_copy.isNeg = 1 - bin_two.isNeg;
    }
    else{
        m_copy.isNeg = bin_two.isNeg;
    }
    *this = m_copy;
    this->Polar_Changer(0);
    return *this;
}

BigInt& BigInt::operator&=(const BigInt& a){
    BigInt m_copy = 0;
    std::vector<char> bin_ans;
    BigInt bin_one = this->getBin();
    BigInt bin_two = a.getBin();
    int len_m = std::min(bin_one._bigint.size(), bin_two._bigint.size());
    bin_ans.resize(len_m,0);
    int spun = 1;
    for(int i = len_m - 1; i > -1; i--){
        bin_ans.at(i) = bin_two._bigint.at(i)*bin_one._bigint.at(i);
        if (bin_ans.at(i)){
            spun = 0;
        }
        if(spun){
            if ((bin_ans.at(i) == 0) && (i != 0)){
                bin_ans.pop_back();
            }
        }
    }
// decryption
    BigInt curr_value = 1;
    bin_one._bigint = bin_ans;
    for (int i = 0; i < bin_ans.size(); i++){
        if (bin_ans.at(i) == 1){
            m_copy += curr_value;
        }
        if (i != bin_ans.size() - 1){
            curr_value *= 2;
        }
    }
    m_copy.isNeg = bin_one.isNeg*bin_two.isNeg;
    *this = m_copy;
    this->Polar_Changer(0);
    return *this;
}

BigInt& BigInt::operator|=(const BigInt& a){
    BigInt m_copy = 0;
    std::vector<char> bin_ans;
    BigInt bin_one = this->getBin();
    BigInt bin_two = a.getBin();
    int len_m = std::max(bin_one._bigint.size(), bin_two._bigint.size());
    bin_ans.resize(len_m,0);
    int spun = 1;
    for(int i = len_m - 1; i > -1; i--){
        if (i > bin_two._bigint.size() - 1){
            bin_ans.at(i) = bin_one._bigint.at(i);
        }
        else{
            if (i > bin_one._bigint.size() - 1){
                bin_ans.at(i) = bin_two._bigint.at(i);
            }
            else{
                if(bin_one._bigint.at(i)){
                    bin_ans.at(i) = 1;
                }
                else{
                    bin_ans.at(i) = bin_two._bigint.at(i);
                }
            }
        }
    }
// decryption
    BigInt curr_value = 1;
    bin_one._bigint = bin_ans;
    for (int i = 0; i < bin_ans.size(); i++){
        if (bin_ans.at(i) == 1){
            m_copy += curr_value;
        }
        if (i != bin_ans.size() - 1){
            curr_value *= 2;
        }
    }
    if (bin_one.isNeg){
        m_copy.isNeg = 1;
    }
    else{
        m_copy.isNeg = bin_two.isNeg;
    }
    *this = m_copy;
    this->Polar_Changer(0);
    return *this;
}

BigInt operator^(const BigInt& a, const BigInt& b){
    BigInt ans = a;
    ans ^= b;
    return ans;
}

BigInt operator&(const BigInt& a, const BigInt& b){
    BigInt ans = a;
    ans &= b;
    return ans;
}

BigInt operator|(const BigInt& a, const BigInt& b){
    BigInt ans = a;
    ans |= b;
    return ans;
}

BigInt::operator std::string() const{
    return this->getBigInt();
}

BigInt::operator int() const{
    int ans = 0;
    int t_pow = 1;
    for (int i = 0; i < this->_bigint.size(); i++){
        ans += t_pow * int(this->_bigint.at(i));
        t_pow *= 10;
    }
    if (this->isNeg){
        ans *= -1;
    }
    return ans;
}

BigInt::operator long long() const{
    long long int ans = 0;
    int t_pow = 1;
    for (int i = 0; i < this->_bigint.size(); i++){
        ans += t_pow * int(this->_bigint.at(i));
        t_pow *= 10;
    }
    if (this->isNeg){
        ans *= -1;
    }
    return ans;
}

size_t BigInt::size() const{
    return (this->_bigint.size()+4);
}

std::ostream& operator<<(std::ostream& o, const BigInt& i){
    o << std::string(i.getBigInt());
    return o;
}
