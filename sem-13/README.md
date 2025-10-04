# Множествено наследяване. Виртуално наследяване. Виртуални таблици при множествено и виртуално наследяване. Диамантен проблем. 

## Множествено наследяване

Клас може да наследява от повече от един базов клас.

```c++
class A 
{ 
public: 
	int a;
};

class B 
{ 
public: 
	int b;
};

class C : public A, public B {};

```

Няма значение, че класа може да не е в началото, има механизъм, чрез който обекта се намира.
```c++
void f(A& obj) {}

void g(B* ptr) {}

int main()
{
	C obj;
	f(obj);
	g(&obj);
}
```

От значение е реда, в който наследяване класовете. 
```c++
// BaseClass = BC

class BC1 {...};
class BC2 {...};
class BC3 {...};

class Der : public BC1, public BC2, public BC3 
{
public:
	Der(...) : BC1(...), BC2(...), BC3(...) // we can permutade those, so BC2(...), BC3(...), BC1(...) is valid and so on...

	Der& operator=(const Person& other)
	{
		if(this != &other)
		{
			BC1::op=(other);
			BC2::op=(other);
			BC3::op=(other);
			// it's best practice to call base class operator= in the order of inheritance
			free();
			copyFrom(other);
		}

		return *this;
	}
};
```

## Диамантен проблем
```c++
class A { public: int x; };

class B : public A {};

class C : public A {};

class D : public B, public C {};

int main() 
{
    D obj;
}
```

Конструктора на ```A``` бива извикан 2 пъти, а ако имахме и деструктор - той също щеше да бъде извикан 2 пъти.
Тоест, обектът ```obj``` има 2 копия на всички данни на базовия клас ```A```, което предизвиква двусмислия/неяснотии(ambiguous behaviour).

## Виртуално наследяване
Решението на горният проблем е използването на виртуално наследяване.
Класовете ```B``` и ```C``` трябва да наследят виртуално ```A```, за да избегнем 2-те копия на ```A```.

Когато използваме ключовата дума ```virtual``` при наследяване, конструкторът по подразбиране на прародителя се извиква по подразбиране, дори ако родителските класове извикват изрично конструктор с параметри. Тоест всеки наследник на клас, който наследява друг като ```virtual```, трябва да избере кой конструктор се вика на прародителя(виртуално наследения клас). В случая ```D```, трябва експлицитно да каже кой конструктор на ```A``` да се извика.

```c++
class A { public: int x; };

class B : virtual public A {};

class C : virtual public A {};

class D : public B, public C {};

int main() 
{
    D obj;
}
```

## Виртуални таблици при множествено и виртуално наследяване
### При множествено наследяване
```c++
class BC1 
{
public:
	virtual void f() {}
	virtual void k() {}
};

class BC2 
{
public:
	virtual void g() {}
};
class BC3
{
public:
	virtual void f() {}
	virtual void t() {}
};

class Der : public BC1, public BC2, public BC3
{
public:
	void f() override {} // always in this situation, bc of BC1::f() and BC3::f()!!!
	void g() override {}
}

int main()
{
	Der d;
	BC1* ptr1 = &d;
	BC2* ptr2 = &d;
	BC3* ptr3 = &d;

	// ptr1 != ptr2 != ptr3

	ptr2->g(); // Der::g()
}
```
Указателя на ```ptr2``` сочи към адреса на BC2, а не към този на Der, затова при множественето наследяване към виртуалната таблица има допълнителен параметър - Δ <br>
**Δ(class)** - колко е отместването на даден клас от началото на наследника му
- Δ(BC1) = 0
- Δ(BC2) = sizeof(BC1)
- Δ(BC3) = sizeof(BC1) + sizeof(BC2)

### При виртуално наследяване
``` c++
class A
{
public:
	virtual void f() {}
	virtual void g() {}
	virtual void k() {}
	virtual void t() {}
};

class B : virtual public A
{
public:
	void g() override {}
};

class C : virtual public A
{
public:
	void f() override {}
};

class D : public B, public C
{
public:
	void t() override {}
};

int main()
{
	D d;
	A* ptr = &d;
	ptr->f();
}
```

| Функция | Отместване |
|---|---|
|  C::f() |  -Δ(A) + Δ(C) |
|  B::g() |  -Δ(A) |
|  D::t() |  -Δ(A) | 
|  A::k() |  0 | 

## Задачи
В една фирма съществуват различни видове служители. Всеки служител има име и служебен номер. Мениджърите ръководят проекти, а инженерите работят по технически задачи. Съществува и служител, наречен **технически мениджър** – той изпълнява едновременно ролите на инженер и мениджър.

1. **Създайте клас `Employee`**, който съдържа:
   - `име` на служителя (низ)
   - `идентификационен номер` (цяло число)
   - метод `printInfo()`, който извежда информацията за служителя

2. **Създайте клас `Manager`**, който:
   - наследява `Employee`
   - съдържа `име на проект` (низ)
   - има собствена имплементация на `printInfo()`

3. **Създайте клас `Engineer`**, който:
   - наследява `Employee`
   - съдържа `техническа специализация` (низ)
   - има собствена имплементация на `printInfo()`

4. **Създайте клас `TechManager`**, който:
   - наследява едновременно от `Manager` и `Engineer`
   - съдържа метод `assignTask(const MyString& task)`, който извежда съобщение от вида:  
     ```
     TechManager [name] assigns task: [task]
     ```
