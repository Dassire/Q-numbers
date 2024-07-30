#ifndef RATIONAL_H_
#define RATIONAL_H_

class Rational {
private:
	int m_num;
	int m_den;

public:
	Rational(int num, int den);
	Rational(const Rational&);
	Rational();
	~Rational();

	Rational copy();

	int numerator()   const;
	int denominator() const;
	char* toString();

	int cmp(const Rational&) const;
	Rational& add(const Rational&);
	Rational& sub(const Rational&);
	// ?
	Rational& simplify();

	// Rational* ?
	Rational& operator  = (const Rational&);
	Rational& operator += (const Rational&);
	Rational& operator -= (const Rational&);
	Rational& operator *= (const Rational&);
	Rational& operator /= (const Rational&);

};

Rational operator + (const Rational&, const Rational&);
Rational operator - (const Rational&, const Rational&);
Rational operator * (const Rational&, const Rational&);
Rational operator / (const Rational&, const Rational&);

// comp
int operator == (const Rational&, const Rational&);
int operator != (const Rational&, const Rational&);
int operator <  (const Rational&, const Rational&);
int operator <= (const Rational&, const Rational&);
int operator >  (const Rational&, const Rational&);
int operator >= (const Rational&, const Rational&);

#endif