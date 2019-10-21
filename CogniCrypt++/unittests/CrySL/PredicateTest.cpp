#include <../../utils/Logger.h>
#include <CrySLParser.h>
#include <CrySLParserEngine.h>
#include <FormatConverter/PredicateConverter.h>
#include <filesystem>
#include <gtest/gtest.h>
#include <iostream>

using namespace CCPP;

/* ============== TEST FIXTURE ============== */

class PredicateTest : public ::testing::Test {

protected:
  const std::string pathToCrySLFiles = "../../../test/CrySL/";

  PredicateConverter *predicateConverter = nullptr;
  std::vector<Predicate> predicates;

  PredicateTest() {}
  virtual ~PredicateTest() {}

  void Initialize(const std::string &CrySLFile) {
    std::cout << "Hello!!!" << std::endl;
    EXPECT_EQ(std::filesystem::exists(CrySLFile), true) << CrySLFile;

    CrySLParserEngine cryslparserengine({CrySLFile});
    EXPECT_EQ(cryslparserengine.parseAndTypecheck(), true);
    auto ast = cryslparserengine.getAllASTs()[0].get();
      auto preds = (ast->getAST()->requiresBlock() || (ast->getAST()->ensures());
      //auto preds = ast->getAST()->ensures();
      auto objCtx = ast->getAST()->objects();
      auto specname = ast->getAST()->spec()->qualifiedName()->getText();

	  predicateConverter = new PredicateConverter(preds, objCtx, specname)
	  auto fm = std::move(predicateConverter->formatConverter());
	  predicates = std::move(fm);
  }

  void SetUp() override { bl::core::get()->set_logging_enabled(false); }

  void TearDown() override {
    if (predicateConverter) {
      std::cout << "Free" << std::endl;
      std::cout << ">FREE" << std::endl;
      delete predicateConverter;
      std::cout << ">>FREE" << std::endl;
      predicateConverter = nullptr;
    }
  }

  void compareResults(std::set<std::string> &expectedFunctionNames) {
    std::string functionName;
    ASSERT_EQ(this->predicates.size(), expectedFunctionNames.size());
    for (const auto &predicate : this->predicates) {
      functionName = predicate.getFunctionName();
      EXPECT_EQ(1,expectedFunctionNames.count(functionName));
    }
    std::cout << "Compare results end" << std::endl;
  }

}; //class fixture


  int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}