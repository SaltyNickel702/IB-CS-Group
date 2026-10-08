#pragma once

#include <vector>
#include <string>
#include <format>

struct CookingPlan {
	virtual std::vector<std::string> cook() = 0;

	std::string getDish() { return dishName; };

	protected:
		CookingPlan(std::string dish) : dishName(dish) {};
	
	private:
		std::string dishName;
};


struct OvenPlan : public CookingPlan {
    OvenPlan(std::string dish) : CookingPlan(dish) {};

    std::vector<std::string> cook() override {
        std::vector<std::string> v {
            "Prepare the oven and baking dish.",
            std::format("Place {} in the baking dish.", getDish()),
            "Bake using the recipe's oven instructions."
        };

        return v;
    };
};

struct StovetopPlan : public CookingPlan {
    StovetopPlan(std::string dish) : CookingPlan(dish) {};

    std::vector<std::string> cook() override {
        std::vector<std::string> v {
            "Prepare the stovetop and pan.",
            std::format("Place {} in the pan.", getDish()),
            "Cook using the recipe's stovetop instructions."
        };

        return v;
    };
};

struct CampingPlan : public CookingPlan {
	CampingPlan(std::string dish) : CookingPlan(dish) {};

	std::vector<std::string> cook() override {
		std::vector<std::string> v {
			"Prepare the portable stove and camping pot.",
			std::format("Place {} in the camping pot.",getDish()),
			"Cook using the recipe's portable-stove instructions."
		};

		return v;
	};
};