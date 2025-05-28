# Умни указатели. Type casting. 

## Умни указатели (Smart Pointers)

Обвиващ клас около обикновен указател, който автоматично освобождава паметта.

### unique_ptr - 1 указател за 1 обект
- не може да се копира – само прехвърляне на собственост чрез std::move

```c++
#include <memory>
#include <iostream>

class А 
{
public:
    А() { std::cout << "А()\n"; }
    ~А() { std::cout << "~А()\n"; }
};

int main() 
{
    std::unique_ptr<А > ptr = std::make_unique<А >();
}
```

### shared_ptr - 1 обект, много указатели
- пази указател към обект и брояч колко указатели са насочени към обекта
- когато броячът стигне, то обектът се изтрива

```c++
#include <memory>
#include <iostream>

class А  
{
public:
    А() { std::cout << "А()\n"; }
	void f() { std::cout << "A::f()"; }
    ~А() { std::cout << "~А()\n"; }
};

int main() 
{
    std::shared_ptr<А> p1 = std::make_shared<А>();
    std::shared_ptr<А> p2 = p1;
	std::shared_ptr<A> p3 = p1;

    p2.reset();
    p3.reset();

    p->f(); // call f() if p exists 
}

```

### weak_ptr – слаба (non-owning) връзка
- сочи към обект, менажиран от shared_ptr
- не увеличава референтния брояч
- не влияе на триенете и може да сочи към вече изтрит обект
- ```weak_ptr``` трябва да има проверки дали обектът е изтрит
```c++
#include <memory>
#include <iostream>

class А 
{
public:
    А() { std::cout << "А()\n"; }
    ~А() { std::cout << "~А()\n"; }
};

int main() 
{
    std::shared_ptr<А> p1 = std::make_shared<А>();

    std::weak_ptr<А> wp = p1; // няма собственост
}
```

## Употреба на умни указатели
| Указател          | Собственост    | Копиране                                                          | Автоматично освобождаване     | Типична употреба                                                    |
| ----------------- | -------------- | ----------------------------------------------------------------- | ----------------------------- | ------------------------------------------------------------------- |
| `std::unique_ptr` | Да             | Не може да се копира<br> Може да се **премести** (`std::move`) | Да                          | Когато един обект притежава ресурс — например в клас                |
| `std::shared_ptr` | Да (споделена) | Може да се копира — брояч на препратки                          | Да (когато броячът стане 0) | Споделена собственост, например при графови структури               |
| `std::weak_ptr`   | Не             | Може да се копира<br> Не увеличава броя препратки              | Не освобождава автоматично  | Използва се за избягване на циклични зависимости между `shared_ptr` |

## Type casting.
Основни видове cast в C++:
- static_cast
- dynamic_cast
- reinterpret_cast
- const_cast

### static_cast
- подходящ за примитивни типове или при наследяване без виртуални методи
- compile time check

```c++
float f = 3.14;
int i = static_cast<int>(f); // безопасно, но губим информация
```

### dynamic_cast
- използва се при полиморфизъм
- при cast-ване към Derived(наследник) клас.
- нужна е поне една виртуална функция.
- runtime check
- може да върне nullptr

```c++
class Base 
{
public:
    virtual void f() {}
};

class Derived : public Base 
{
public:
    void g() {}
};

int main() 
{
    Base* b = new Derived();
    Derived* d = dynamic_cast<Derived*>(b);
    if (d) d->g(); // безопасно проверено по време на изпълнение
}
```

### const_cast
- използва се за добавяне/премахване на const към променлива

```c++
void print(char* str) 
{
    std::cout << str << "\n";
}

int main() 
{
    const char* name = "Hello";
    print(const_cast<char*>(name));
}
```

### reinterpret_cast
- преобразуване на указател от произволен тип към указател от произволен тип

```c++
int* p = new int(10);
char* c = reinterpret_cast<char*>(p);
```

## Задачи
**Задача 1:** Създайте шаблонен клас SharedPtr<T>, който симулира основната функционалност на std::shared_ptr, включително поддръжка на слаби указатели (WeakPtr<T>)
