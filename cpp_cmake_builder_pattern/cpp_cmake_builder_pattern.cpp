// cpp_cmake_builder_pattern.cpp: определяет точку входа для приложения.
//

#include "cpp_cmake_builder_pattern.h"

// Загальний клас, 
// об'єкти якого формуються будівником
class Pizza
{
private:
	std::string dough;
	std::string sauce;
	std::string topping;

public:
	Pizza() { }
	~Pizza() { }

	void SetDough(const std::string& d) { dough = d; }
	void SetSauce(const std::string& s) { sauce = s; }
	void SetTopping(const std::string& t) { topping = t; }

	void ShowPizza()
	{
		std::cout << " Yummy !!!" << std::endl
			<< "Pizza with Dough as " << dough
			<< ", Sauce as " << sauce
			<< " and Topping as " << topping
			<< " !!! " << std::endl;
	}
};

// Абстрактний будівник, який надає інтерфейс
// для функцій будівників об’єктів необхідних типів
class PizzaBuilder
{
protected:
	std::shared_ptr<Pizza> pizza;
public:
	PizzaBuilder() {}
	virtual ~PizzaBuilder() {}
	std::shared_ptr<Pizza> GetPizza() { return pizza; }

	void createNewPizzaProduct() { pizza.reset(new Pizza); }

	virtual void buildDough() = 0;
	virtual void buildSauce() = 0;
	virtual void buildTopping() = 0;
};

// Безпосередня реалізація будівника 1
class HawaiianPizzaBuilder : public PizzaBuilder
{
public:
	HawaiianPizzaBuilder() : PizzaBuilder() {}
	~HawaiianPizzaBuilder() {}

	void buildDough() { pizza->SetDough("cross"); }
	void buildSauce() { pizza->SetSauce("mild"); }
	void buildTopping() { pizza->SetTopping("ham and pineapple"); }
};

// Безпосередня реалізація будівника 2
class SpicyPizzaBuilder : public PizzaBuilder
{
public:
	SpicyPizzaBuilder() : PizzaBuilder() {}
	~SpicyPizzaBuilder() {}

	void buildDough() { pizza->SetDough("pan baked"); }
	void buildSauce() { pizza->SetSauce("hot"); }
	void buildTopping() { pizza->SetTopping("pepperoni and salami"); }
};

// Безпосередня реалізація будівника 3
class ChickMushPizzaBuilder : public PizzaBuilder
{
public:
	ChickMushPizzaBuilder() : PizzaBuilder() {}
	~ChickMushPizzaBuilder() {}

	void buildDough() { pizza->SetDough("oven baked"); }
	void buildSauce() { pizza->SetSauce("\"Chumak\""); }
	void buildTopping() { pizza->SetTopping("chicken and mushrooms"); }
};

// Клас, що керує виконанням будівників
class Waiter
{
private:
	PizzaBuilder* pizzaBuilder;
public:
	Waiter() : pizzaBuilder(nullptr) {}
	~Waiter() { }

	void SetPizzaBuilder(PizzaBuilder* b)
	{
		pizzaBuilder = b;
	}
	std::shared_ptr<Pizza> GetPizza()
	{
		return pizzaBuilder->GetPizza();
	}
	void ConstructPizza()
	{
		pizzaBuilder->createNewPizzaProduct();
		pizzaBuilder->buildDough();
		pizzaBuilder->buildSauce();
		pizzaBuilder->buildTopping();
	}
};

// Основний код, в якому керуючий клас Waiter формує два об’єкти, 
// для яких реалізовано безпосередні будівники 
// HawaiianPizzaBuilder та SpicyPizzaBuilder
int main()
{
	//initializing
	Waiter waiter;
	HawaiianPizzaBuilder hawaiianPizzaBuilder;
	SpicyPizzaBuilder spicyPizzaBuilder;
	ChickMushPizzaBuilder chickmushPizzaBuilder;

	bool needexit = false;

	while (true)
	{

		std::cout << "Select pizza type (1/2/3); 0 to exit" << std::endl;
		int sel = 0;
		std::cin >> sel;

		switch (sel) {
		case 1:
		{
			waiter.SetPizzaBuilder(&hawaiianPizzaBuilder);
			break;
		}
		case 2:
		{
			waiter.SetPizzaBuilder(&spicyPizzaBuilder);
			break;
		}
		case 3:
		{
			waiter.SetPizzaBuilder(&chickmushPizzaBuilder);
			break;
		}
		default:
		{
			needexit = true;
			break;
		} }

		if (needexit) break;
		waiter.ConstructPizza();
		std::shared_ptr<Pizza> pizza = waiter.GetPizza();
		pizza->ShowPizza();

	}

	system("pause");

	return EXIT_SUCCESS;
}

