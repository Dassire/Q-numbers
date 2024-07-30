#include <stdlib.h>
#include "stdio.h"
#include "string.h"

#include "Rational.h"
#include "PGCD.h"

char* intToString(int n) {
	size_t size=2;
	int tmp=abs(n);
	char* r;
	while(tmp>9) {
		size++;
		tmp=tmp/10;
	}
	if(n<0) {
		size++;
	}
	r=new char[size];
	sprintf(r, "%d", n);
	return r;
}

Rational::Rational(int num, int den) : m_num(num), m_den(den) {}

Rational::Rational(const Rational& x) : m_num(x.m_num), m_den(x.m_den) {}

Rational::Rational() : m_num(0), m_den(1) {}

Rational::~Rational() {
	// del num;
	// del m_den
}

Rational Rational::copy() {
	Rational r(*this);
	return r;
}

int Rational::numerator() const { return m_num; }
int Rational::denominator() const { return m_den; }

char* Rational::toString() {
	// size_t size=2; // / + num + den + '\0'
	// int tmp=m_num;
	char* top, *bot, *r;
	/*
	r;
	while(tmp>9) {
		size++;
		tmp=tmp/10;
	}
	tmp=m_den;
	while(tmp>9) {
		size++;
		tmp=tmp/10;
	}
	if(m_num<0) {
		size++;
	}
	if(m_den<0) {
		size++;
	}
	*/

	top=intToString(m_num);
	if(m_den==1) {
		return top;
	}

	bot=intToString(m_den);
	// size+=strlen(top)+strlen(bot);

	r=new char[2+strlen(top)+strlen(bot)]; // 2 for / and \0
	sprintf(r, "%s/%s", top, bot);
	delete[] top;
	delete[] bot;
	return r;
}

int Rational::cmp(const Rational& right) const {
	// int gcd1=PGCD(m_num, m_den);
	// int gcd2=PGCD(right.m_num,right.m_den);
	int gcd;
	int lnum=m_num, lden=m_den, rnum=right.m_num, rden=right.m_den;
	if(lden<0) {
		lnum=0-lnum;
		lden=0-lden;
	}
	if(rden<0) {
		rnum=0-rnum;
		rden=0-rden;
	}
	gcd=PGCD(lden, rden, NULL, NULL);
	return (lnum*(rden/gcd))-((lden/gcd)*rnum);
}

Rational& Rational::add(const Rational& right) {
	if(m_den!=right.m_den) { // can't be the same object
		m_num=(m_num*right.m_den)+(m_den*right.m_num);
		m_den*=right.m_den;
	} else {
		m_num+=right.m_num;
	}
	return *this;
}

Rational& Rational::sub(const Rational& right) {
	if(m_den!=right.m_den) { // can't be the same object
		m_num=(m_num*right.m_den)-(m_den*right.m_num);
		m_den*=right.m_den;
	} else {
		m_num-=right.m_num;
	}
	return *this;
}

/* // Other :

void Rational::sub(const Rational& right) {
	m_num*=-1;
	add(right);
	m_num*=-1;
}

 */

Rational& Rational::simplify() {
	int gcd;

	if(m_den<0) {
		if(m_den==0) exit(1);
		m_den= -m_den;
		m_num= -m_num;
	}

	gcd=PGCD(m_num, m_den, NULL, NULL);
	m_den/=gcd;
	m_num/=gcd;
	return *this;
}

Rational& Rational::operator =  (const Rational& right) {
	m_num=right.m_num; // .copy();
	m_den=right.m_den;
	return *this;
}

Rational& Rational::operator += (const Rational& right) {
	add(right);
	return *this;
}

Rational& Rational::operator -= (const Rational& right) {
	sub(right);
	return *this;
}

Rational& Rational::operator *= (const Rational& right) {
	m_num*=right.m_num;
	m_den*=right.m_den;
	return *this;
}

Rational& Rational::operator /= (const Rational& right) {
	int tmp=right.m_num; // in case of right===this
	if(right.m_num==0) { exit(1); }
	m_num*=right.m_den;
	m_den*=tmp;
	return *this;
}

Rational operator + (const Rational& left, const Rational& right) {
	Rational r(left);
	r.add(right);
	return r;
}

Rational operator - (const Rational& left, const Rational& right) {
	Rational r(left);
	r.sub(right);
	return r;
}

Rational operator * (const Rational& left, const Rational& right) {
	Rational r(left);
	r*=right;
	return r;
}

Rational operator / (const Rational& left, const Rational& right) {
	Rational r(left);
	r/=right;
	return r;
}

int operator == (const Rational& left, const Rational& right) {
	return left.cmp(right)==0;
}

int operator != (const Rational& left, const Rational& right) {
	return left.cmp(right)!=0;
}

int operator <  (const Rational& left, const Rational& right) {
	return left.cmp(right)<0;
}

int operator <= (const Rational& left, const Rational& right) {
	return left.cmp(right)<=0;
}

int operator >  (const Rational& left, const Rational& right) {
	return left.cmp(right)>0;
}

int operator >= (const Rational& left, const Rational& right) {
	return left.cmp(right)>=0;
}
