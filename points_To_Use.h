#pragma once
class points_To_Use
{
public:
	points_To_Use();
	points_To_Use(short x, short y, bool lineBegins);
	points_To_Use(const points_To_Use& p);

	short getX() const;
	void setX(const short x);
	short getY() const;
	void setY(const short y);
	bool islineBegins() const;

	points_To_Use& operator= (const points_To_Use& other);

	bool operator== (const points_To_Use& rhs) const;

private:
	short _x;
	short _y;
	bool  lineBegins;
   
};

