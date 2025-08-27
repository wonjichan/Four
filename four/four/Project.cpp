#include <iostream>
#include <vector>
#include <string>
#include <map>

class PotionRecipe {
public:
    std::string potionName;
    std::vector<std::string> ingredients;

    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : potionName(name), ingredients(ingredients) {
    }
};

class StockManager {
private:
    std::map<std::string, int> potionStock;
    const int MAX_STOCK = 3;

public:
    void initializeStock(const std::string& potionName) {
        potionStock[potionName] = MAX_STOCK;
    }

    bool dispensePotion(const std::string& potionName) {
        if (potionStock.count(potionName) == 0) {
            std::cout << "해당 물약은 존재하지 않습니다.\n";
            return false;
        }
        if (potionStock[potionName] > 0) {
            potionStock[potionName]--;
            std::cout << potionName << " 물약을 지급했습니다. 남은 재고: " << potionStock[potionName] << std::endl;
            return true;
        }
        else {
            std::cout << potionName << " 물약의 재고가 없습니다.\n";
            return false;
        }
    }

    void returnPotion(const std::string& potionName) {
        if (potionStock.count(potionName) == 0) {
            std::cout << "해당 물약은 존재하지 않습니다.\n";
            return;
        }
        if (potionStock[potionName] < MAX_STOCK) {
            potionStock[potionName]++;
            std::cout << potionName << " 물약이 반환되어 재고가 " << potionStock[potionName] << "개가 되었습니다.\n";
        }
        else {
            std::cout << potionName << " 물약의 재고가 최대치입니다.\n";
        }
    }

    int getStock(const std::string& potionName) const {
        if (potionStock.count(potionName) == 0) return 0;
        return potionStock.at(potionName);
    }

    void displayAllStocks() const {
        std::cout << "\n--- [ 물약 재고 현황 ] ---\n";
        for (const auto& pair : potionStock) {
            std::cout << pair.first << ": " << pair.second << "개\n";
        }
        std::cout << "-------------------------\n";
    }
};

class RecipeManager {
private:
    std::vector<PotionRecipe> recipes;

public:
    // 레시피 추가 시 포션 이름 중복 체크
    bool addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        for (const auto& r : recipes) {
            if (r.potionName == name) {
                std::cout << "이미 존재하는 물약 이름입니다.\n";
                return false;
            }
        }
        recipes.push_back(PotionRecipe(name, ingredients));
        std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다.\n";
        return true;
    }

    void displayAllRecipes() const {
        if (recipes.empty()) {
            std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
            return;
        }

        std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
        for (const auto& recipe : recipes) {
            std::cout << "- 물약 이름: " << recipe.potionName << std::endl;
            std::cout << "  > 필요 재료: ";
            for (size_t j = 0; j < recipe.ingredients.size(); ++j) {
                std::cout << recipe.ingredients[j];
                if (j < recipe.ingredients.size() - 1) std::cout << ", ";
            }
            std::cout << std::endl;
        }
        std::cout << "---------------------------\n";
    }

    PotionRecipe* findRecipeByName(const std::string& name) {
        for (auto& r : recipes) {
            if (r.potionName == name) return &r;
        }
        return nullptr;
    }

    std::vector<PotionRecipe> findRecipesByIngredient(const std::string& ingredient) {
        std::vector<PotionRecipe> found;
        for (const auto& r : recipes) {
            for (const auto& ingr : r.ingredients) {
                if (ingr == ingredient) {
                    found.push_back(r);
                    break;
                }
            }
        }
        return found;
    }

    const std::vector<PotionRecipe>& getAllRecipes() const {
        return recipes;
    }
};

class AlchemyWorkshop {
private:
    RecipeManager recipeManager;
    StockManager stockManager;

public:
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        if (recipeManager.addRecipe(name, ingredients)) {
            stockManager.initializeStock(name);
        }
    }

    void displayAllRecipes() const {
        recipeManager.displayAllRecipes();
    }

    void searchByName(const std::string& name) {
        PotionRecipe* recipe = recipeManager.findRecipeByName(name);
        if (recipe) {
            std::cout << "- 물약 이름: " << recipe->potionName << std::endl;
            std::cout << "  > 필요 재료: ";
            for (size_t i = 0; i < recipe->ingredients.size(); ++i) {
                std::cout << recipe->ingredients[i];
                if (i < recipe->ingredients.size() - 1) std::cout << ", ";
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "해당 이름의 물약 레시피가 없습니다.\n";
        }
    }

    void searchByIngredient(const std::string& ingredient) {
        std::vector<PotionRecipe> found = recipeManager.findRecipesByIngredient(ingredient);
        if (found.empty()) {
            std::cout << "해당 재료를 포함한 레시피가 없습니다.\n";
            return;
        }
        std::cout << "\n--- '" << ingredient << "' 재료를 포함한 레시피 ---\n";
        for (const auto& r : found) {
            std::cout << "- 물약 이름: " << r.potionName << std::endl;
            std::cout << "  > 필요 재료: ";
            for (size_t i = 0; i < r.ingredients.size(); ++i) {
                std::cout << r.ingredients[i];
                if (i < r.ingredients.size() - 1) std::cout << ", ";
            }
            std::cout << std::endl;
        }
        std::cout << "---------------------------\n";
    }

    void dispensePotion(const std::string& potionName) {
        stockManager.dispensePotion(potionName);
    }

    void returnPotion(const std::string& potionName) {
        stockManager.returnPotion(potionName);
    }

    void displayStock() const {
        stockManager.displayAllStocks();
    }
};

int main() {
    AlchemyWorkshop workshop;

    while (true) {
        std::cout << "\n⚗️ 연금술 공방 관리 시스템" << std::endl;
        std::cout << "1. 레시피 추가" << std::endl;
        std::cout << "2. 모든 레시피 출력" << std::endl;
        std::cout << "3. 물약 이름으로 검색" << std::endl;
        std::cout << "4. 재료로 검색" << std::endl;
        std::cout << "5. 물약 지급" << std::endl;
        std::cout << "6. 물약 반환" << std::endl;
        std::cout << "7. 재고 현황 보기" << std::endl;
        std::cout << "8. 종료" << std::endl;
        std::cout << "선택: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            std::string name;
            std::cout << "물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            std::vector<std::string> ingredients_input;
            std::string ingredient;
            std::cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << std::endl;

            while (true) {
                std::cout << "재료 입력: ";
                std::getline(std::cin, ingredient);
                if (ingredient == "끝") break;
                ingredients_input.push_back(ingredient);
            }

            if (!ingredients_input.empty()) {
                workshop.addRecipe(name, ingredients_input);
            }
            else {
                std::cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
            }

        }
        else if (choice == 2) {
            workshop.displayAllRecipes();

        }
        else if (choice == 3) {
            std::cout << "검색할 물약 이름: ";
            std::string name;
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);
            workshop.searchByName(name);

        }
        else if (choice == 4) {
            std::cout << "검색할 재료 이름: ";
            std::string ingredient;
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, ingredient);
            workshop.searchByIngredient(ingredient);

        }
        else if (choice == 5) {
            std::cout << "지급할 물약 이름: ";
            std::string potionName;
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, potionName);
            workshop.dispensePotion(potionName);

        }
        else if (choice == 6) {
            std::cout << "반환할 물약 이름: ";
            std::string potionName;
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, potionName);
            workshop.returnPotion(potionName);

        }
        else if (choice == 7) {
            workshop.displayStock();

        }
        else if (choice == 8) {
            std::cout << "공방 문을 닫습니다..." << std::endl;
            break;

        }
        else {
            std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
        }
    }

    return 0;
}