#include "Tests.h" // Includes gtest/gtest.h and "../Manager.h"
#include <string>

using namespace ClassProject;

// Define the Test Fixture class
class ManagerTest : public ::testing::Test {
protected:
    Manager manager;

    // These constants are defined by the BDD specification (0 for False, 1 for True)
    const BDD_ID FALSE_ID = 0;
    const BDD_ID TRUE_ID = 1;

    void SetUp() override {
        // Assert that the terminal nodes are set up correctly upon construction.
        // The unique table must contain False (0) and True (1) immediately.
        ASSERT_EQ(manager.uniqueTableSize(), 2);
    }
};


TEST_F(ManagerTest, False_Node_ID) {
    std::cout << "\n--- Testing FalseID ---" << std::endl;
    std::cout << "Testing False() returns " << FALSE_ID << std::endl;
    BDD_ID result = manager.False();
    std::cout << "False() returned: " << result << std::endl;
    EXPECT_EQ(result, FALSE_ID);
}

TEST_F(ManagerTest, True_Node_ID) {
    std::cout << "\n--- Testing TrueID ---" << std::endl;
    BDD_ID result = manager.True();
    std::cout << "True() returned: " << result << std::endl;
    EXPECT_EQ(result, TRUE_ID);
}

TEST_F(ManagerTest, IsConstant_PositiveChcek) {
    std::cout << "\n---Testing is Constant for False and True ID ---" << std::endl;
    std::cout << "isConstant(TRUE_ID): " << manager.isConstant(TRUE_ID) << std::endl;
    std::cout << "isConstant(FALSE_ID): " << manager.isConstant(FALSE_ID) << std::endl;
    EXPECT_TRUE(manager.isConstant(TRUE_ID));
    EXPECT_TRUE(manager.isConstant(FALSE_ID));
}

TEST_F(ManagerTest, IsVariable_NegativeCheck) {
    std::cout << "\n--- Testing uniqueTableSize() == 2 ---" << std::endl;
    std::cout << "Testing isVariable returns false for constants" << std::endl;
    std::cout << "isVariable(TRUE_ID): " << manager.isVariable(TRUE_ID) << std::endl;
    std::cout << "isVariable(FALSE_ID): " << manager.isVariable(FALSE_ID) << std::endl;
    EXPECT_FALSE(manager.isVariable(TRUE_ID));
    EXPECT_FALSE(manager.isVariable(FALSE_ID));
}

TEST_F(ManagerTest, UniqueTableSize_InitializesToTwo) {
    std::cout << "\n--- Testing uniqueTableSize() == 2 ---" << std::endl;
    size_t size = manager.uniqueTableSize();
    std::cout << "uniqueTableSize(): " << size << std::endl;
    EXPECT_EQ(size, 2);
}



TEST_F(ManagerTest, Test_Create_Var) {
    std::cout << "\n--- Test_Create_Var ---" << std::endl;

    size_t initial_size = manager.uniqueTableSize();
    std::cout << "Initial uniqueTableSize: " << initial_size << std::endl;

    //std::cout << "Creating first variable 'a'..." << std::endl;
    BDD_ID a_id = manager.createVar("a");
    //std::cout << "First var ID: " << a_id << std::endl;
    EXPECT_EQ(a_id, 2);

    size_t size_after_first = manager.uniqueTableSize();
    std::cout << "Size after first var: " << size_after_first << std::endl;
    EXPECT_EQ(size_after_first, initial_size + 1);

    //std::cout << "Creating second variable 'b'..." << std::endl;
    BDD_ID b_id = manager.createVar("b");
    //std::cout << "Second var ID: " << b_id << std::endl;
    EXPECT_EQ(b_id, 3);

    size_t size_after_second = manager.uniqueTableSize();
    std::cout << "Size after second var: " << size_after_second << std::endl;
    EXPECT_EQ(size_after_second, initial_size + 2);

    //std::cout << "Creating duplicate variable 'a'..." << std::endl;
    BDD_ID a_copy_id = manager.createVar("a");
    // size_t size_after_duplicate = manager.uniqueTableSize();

    //std::cout << "Duplicate var ID: " << a_copy_id << std::endl;
    //std::cout << "Expected (first var ID): " << a_id << std::endl;
    EXPECT_EQ(a_copy_id, a_id) << "If a label that already exists is passed as an input, then don't add the entry and return the id of the first label";

    size_t final_size = manager.uniqueTableSize();
    std::cout << "Final uniqueTableSize: " << final_size << std::endl;
    EXPECT_EQ(final_size, initial_size + 2);
}

TEST_F(ManagerTest, IsConstant_NegativeChcek) {
    std::cout << "\n--- IsConstant_NegativeCheck ---" << std::endl;
    //std::cout << "Creating variable 'a'..." << std::endl;
    BDD_ID a_id = manager.createVar("a");
    //std::cout << "Variable ID: " << a_id << std::endl;
    std::cout << "isConstant(" << a_id << "): " << manager.isConstant(a_id) << std::endl;
    EXPECT_FALSE(manager.isConstant(a_id));
}

TEST_F(ManagerTest, IsVariable_PositiveCheck) {
    std::cout << "\n--- IsVariable_PositiveCheck ---" << std::endl;
    //std::cout << "Creating variable 'a'..." << std::endl;
    BDD_ID a_id = manager.createVar("a");
    //std::cout << "Variable ID: " << a_id << std::endl;
    std::cout << "isVariable(" << a_id << "): " << manager.isVariable(a_id) << std::endl;
    EXPECT_TRUE(manager.isVariable(a_id));
}


TEST_F(ManagerTest, TopVariable_ID) {
    std::cout << "\n--- Test_Top_Var_ID ---" << std::endl;
    BDD_ID a_id = manager.createVar("a");
    BDD_ID b_id = manager.createVar("b");
    //std::cout << "Created variables: a(ID=" << a_id << "), b(ID=" << b_id << ")" << std::endl;

    EXPECT_EQ(manager.topVar(a_id), a_id) << "TopVar ID of a 'simple' variable must be its own ID";
    EXPECT_EQ(manager.topVar(b_id), b_id) << "TopVar ID of a 'simple' variable must be its own ID";

    std::cout << "topVar(" << a_id << ") = " << manager.topVar(a_id)
              << ", topVar(" << b_id << ") = " << manager.topVar(b_id) << std::endl;

    EXPECT_EQ(manager.topVar(FALSE_ID), FALSE_ID) << "TopVar ID of the constant False, must be 0";
    EXPECT_EQ(manager.topVar(TRUE_ID), TRUE_ID) << "TopVar ID of the constant True, must be 1";

    std::cout << "topVar(FALSE_ID) = " << manager.topVar(FALSE_ID)
              << ", topVar(TRUE_ID) = " << manager.topVar(TRUE_ID) << std::endl;




}

TEST_F(ManagerTest, TopVariable_ID_ComplexNodes) {
    std::cout << "\n--- Test_Top_Var_ID_Complex ---" << std::endl;
    BDD_ID a_id = manager.createVar("a");

    BDD_ID x_id = manager.ite(a_id, FALSE_ID, TRUE_ID);
    EXPECT_EQ(manager.topVar(x_id), a_id)
        << "TopVar of the complex node x must be set to the highest-priority variable used in its definition";


}


TEST_F(ManagerTest, TopVariable_Label) {
    std::cout << "\n--- Test_Top_Var_Label ---" << std::endl;

    BDD_ID a_id = manager.createVar("a");
    BDD_ID b_id = manager.createVar("b");
    //std::cout << "Created variables: a(ID=" << a_id << "), b(ID=" << b_id << ")" << std::endl;

    EXPECT_EQ(manager.getTopVarName(a_id), "a") << "Label of a 'simple' variable must be its own label";
    EXPECT_EQ(manager.getTopVarName(b_id), "b") << "Label of a 'simple' variable must be its own label";

    std::cout << "getTopVarName(" << a_id << ") = '" << manager.getTopVarName(a_id)
              << "', getTopVarName(" << b_id << ") = '" << manager.getTopVarName(b_id) << "'" << std::endl;

    EXPECT_EQ(manager.getTopVarName(FALSE_ID), "False") << "Label of the constant False, must be 'False'";
    EXPECT_EQ(manager.getTopVarName(TRUE_ID), "True") << "Label of the constant True, must be 'True'";

    std::cout << "getTopVarName(FALSE_ID) = '" << manager.getTopVarName(FALSE_ID)
              << "', getTopVarName(TRUE_ID) = '" << manager.getTopVarName(TRUE_ID) << "'" << std::endl;



}

TEST_F(ManagerTest, TopVariable_Label_ComplexNodes) {
    std::cout << "\n--- Test_Top_Var_Label_Complex ---" << std::endl;
    BDD_ID a_id = manager.createVar("a");

    BDD_ID x_id = manager.ite(a_id, FALSE_ID, TRUE_ID);
    EXPECT_EQ(manager.getTopVarName(x_id), "a")
        << "TopVarName of the complex node x must be set to the highest-priority variable used in its definition";

}


TEST_F(ManagerTest, ITE_BaseCase) {
    std::cout << "\n--- Test_ITE ---" << std::endl;
    std::cout << "Simple Case, no recursion" << std::endl;



    EXPECT_EQ(manager.ite(TRUE_ID, FALSE_ID, FALSE_ID), FALSE_ID) << "ITE(i, t, t) should return t (False).";
    EXPECT_EQ(manager.ite(FALSE_ID, TRUE_ID, TRUE_ID), TRUE_ID) << "ITE(i, t, t) should return t (True).";


    EXPECT_EQ(manager.ite(TRUE_ID, FALSE_ID, TRUE_ID), FALSE_ID) << "ITE(True, t, e) should return t (False).";


    EXPECT_EQ(manager.ite(FALSE_ID, TRUE_ID, FALSE_ID), FALSE_ID) << "ITE(False, t, e) should return e (False).";

    BDD_ID a_id = manager.createVar("a"); // ID 2
    EXPECT_EQ(manager.ite(a_id, TRUE_ID, FALSE_ID), a_id)
        << "ITE(a, True, False) must return the ID of variable 'a' (2).";
}


TEST_F(ManagerTest, ComplexNode_Properties) {
    std::cout << "\n--- Test_Complex_Nodes_Properties ---" << std::endl;

    BDD_ID a_id = manager.createVar("a"); // ID 2

    // This creates a new complex node (e.g., ID 4).
    BDD_ID x_id = manager.ite(a_id, FALSE_ID, TRUE_ID);

    // 1. Check ID and Size
    EXPECT_GT(x_id, TRUE_ID) << "x must be a non-terminal ID (> 1).";
    EXPECT_EQ(manager.uniqueTableSize(), 4) << "Unique table must increase by 1 to store the new complex node x.";

    // 2. Check Classifications
    EXPECT_FALSE(manager.isConstant(x_id)) << "x must not be a constant.";
    EXPECT_FALSE(manager.isVariable(x_id)) << "x must not be a variable node.";
}



TEST_F(ManagerTest, ITE_PreventsDuplicates) {
    std::cout << "\n--- Test_ITE_PreventDuplicates ---" << std::endl;

    BDD_ID a_id = manager.createVar("a"); // ID 2
    size_t initial_size = manager.uniqueTableSize(); // Should be 3 (0, 1, a)


    BDD_ID x_id = manager.ite(a_id, FALSE_ID, TRUE_ID);

    // Verify it was added (size is now 4)
    EXPECT_EQ(manager.uniqueTableSize(), initial_size + 1) << "First ITE call must add the node.";

    // 2. Call the exact same ITE operation again
    BDD_ID x_copy_id = manager.ite(a_id, FALSE_ID, TRUE_ID);

    // CRITICAL CHECK: The two IDs must be IDENTICAL
    EXPECT_EQ(x_id, x_copy_id)
        << "Second call to ITE with identical inputs must return the existing ID (canonical form).";

    // CRITICAL CHECK: The size must NOT have increased
    EXPECT_EQ(manager.uniqueTableSize(), initial_size + 1)
        << "Unique table size must NOT increase after the second identical call.";
}


TEST_F(ManagerTest, ITE_Recursion) {
    std::cout << "\n--- Test_ITE_Recursion ---" << std::endl;


    BDD_ID a_id = manager.createVar("a");
    BDD_ID b_id = manager.createVar("b");
    size_t initial_size = manager.uniqueTableSize();

    // The function to compute: F = a AND b = ITE(a, b, False)
    // - High branch (a=1) = ITE(True, b, False) = b
    // - Low branch (a=0)  = ITE(False, b, False) = False

    // The resulting node should be: High=b, Low=False, TopVar=a
    BDD_ID and_ab_id = manager.ite(a_id, b_id, FALSE_ID);
    //BDD_ID and_ba_id = manager.ite(b_id, a_id, FALSE_ID);

    // 1. Check ID and Size
    EXPECT_EQ(and_ab_id, b_id + 1) << "The new node must have the next sequential ID (4).";
    EXPECT_EQ(manager.uniqueTableSize(), initial_size + 1) << "Size must increase by 1 for the new complex node.";

    //BDD_ID and_ba_id = manager.ite(b_id, a_id, FALSE_ID);

    // 2. Check TopVar
    //EXPECT_EQ(manager.topVar(and_ba_id), a_id) << "The top variable must be the highest priority variable.";

    //REMEMBER: CHECK SPECIAL CASE IF LOW==HIGH, then return the child instead of creating a new node
    //Node: var = x3, low = N5, high = N5
    //ASK ABOUT HIDDEN REDUCTION
}


TEST_F(ManagerTest, ITE_Reduction_ReturnsHighIfHighEqualsLow) {
    std::cout << "\n--- Test_Hidden_Reduction (LOW==HIGH) ---" << std::endl;
    BDD_ID a_id = manager.createVar("a");
    BDD_ID b_id = manager.createVar("b");

    // Check reduction with a simple variable 'b'
    BDD_ID result_id = manager.ite(a_id, b_id, b_id);

    // CRITICAL CHECK: Must return 'b's ID, not a new node ID.
    EXPECT_EQ(result_id, b_id) << "ITE(i, t, t) must return t, even if i is a variable.";

    // Check that no new node was created (size must be 4: 0, 1, a, b)
    EXPECT_EQ(manager.uniqueTableSize(), 4) << "Unique table size must not increase due to reduction.";
}


TEST_F(ManagerTest, ITE_Ordering_SplitsOnHighestPriorityVar) {
    std::cout << "\n--- Test_Ordering_Splits_On_Highest_Priority_Var ---" << std::endl;

    // Test: F = ITE(b, a, False). The function is actually a AND b.
    // The implementation must internally split on 'a' (the top var).
    BDD_ID a_id = manager.createVar("a");
    BDD_ID b_id = manager.createVar("b");
    // 1. Compute the simple AND operation for comparison
    BDD_ID and_ab_id = manager.ite(a_id, b_id, FALSE_ID);

    // 2. Compute the operation that attempts to violate the order
    BDD_ID reverse_ite_id = manager.ite(b_id, a_id, FALSE_ID);

    // CRITICAL CHECK: Due to the canonical BDD rules, the results must be identical.
    EXPECT_EQ(reverse_ite_id, and_ab_id)
        << "Result must match the canonical form, proving the manager split on 'a' first, not 'b'.";
}



TEST_F(ManagerTest, NOT) {
    std::cout << "\n--- Test_NOT ---" << std::endl;
    // SETUP: Create a variable 'a'
    BDD_ID a_id = manager.createVar("a");

    // 1. Check Trivial Negations (Constants)
    EXPECT_EQ(manager.neg(TRUE_ID), FALSE_ID) << "NOT(True) must be False (0).";
    EXPECT_EQ(manager.neg(FALSE_ID), TRUE_ID) << "NOT(False) must be True (1).";

    // 2. Check Variable Negation
    BDD_ID not_a_id = manager.neg(a_id);

    // The result should match the canonical NOT(a) node created earlier by ITE.
    BDD_ID canonical_not_a = manager.ite(a_id, FALSE_ID, TRUE_ID);

    // CRITICAL CHECK: The ID returned by neg must match the canonical ITE result.
    EXPECT_EQ(not_a_id, canonical_not_a)
        << "Negation result must match the canonical ITE(a, False, True) node.";

    // 3. Check Double Negation (Idempotence)
    EXPECT_EQ(manager.neg(not_a_id), a_id) << "NOT(NOT(a)) must return 'a' (Idempotence).";
}



TEST_F(ManagerTest, AND2) {
    std::cout << "\n--- Test_AND2 ---" << std::endl;
    // SETUP: Create two variables
    BDD_ID a_id = manager.createVar("a"); // ID 2
    BDD_ID b_id = manager.createVar("b"); // ID 3

    // 1. Check Trivial AND (Constants)
    EXPECT_EQ(manager.and2(TRUE_ID, FALSE_ID), FALSE_ID) << "True AND False must be False.";
    EXPECT_EQ(manager.and2(TRUE_ID, TRUE_ID), TRUE_ID) << "True AND True must be True.";
    EXPECT_EQ(manager.and2(FALSE_ID, TRUE_ID), FALSE_ID) << "False AND True must be False.";
    EXPECT_EQ(manager.and2(FALSE_ID, FALSE_ID), FALSE_ID) << "False AND False must be False.";

    // 2. Check AND with itself (Idempotence)
    EXPECT_EQ(manager.and2(a_id, a_id), a_id) << "a AND a must be a.";

    // 3. Check Variable AND
    BDD_ID and_ab_id = manager.and2(a_id, b_id);

    // The result should match the canonical AND(a, b) node created earlier by ITE.
    BDD_ID canonical_and_ab = manager.ite(a_id, b_id, FALSE_ID);

    // CRITICAL CHECK: The ID returned by and2 must match the canonical ITE result.
    EXPECT_EQ(and_ab_id, canonical_and_ab)
        << "AND result must match the canonical ITE(a, b, False) node.";
}




// --- Phase 4: Test Case 3 (OR) ---
TEST_F(ManagerTest, OR2) {
    std::cout << "\n--- Test_OR2 ---" << std::endl;
    // SETUP: Create two variables
    BDD_ID a_id = manager.createVar("a"); // ID 2
    BDD_ID b_id = manager.createVar("b"); // ID 3



    // Check Trivial OR
    EXPECT_EQ(manager.or2(FALSE_ID, FALSE_ID), FALSE_ID) << "False OR False must be False.";
    EXPECT_EQ(manager.or2(TRUE_ID, FALSE_ID), TRUE_ID) << "True OR False must be True.";;
    EXPECT_EQ(manager.or2(FALSE_ID, TRUE_ID), TRUE_ID)<< "False OR True must be True.";;
    EXPECT_EQ(manager.or2(TRUE_ID, TRUE_ID), TRUE_ID)<< "True OR True must be True.";;

    // Check Variable OR
    BDD_ID or_ab_id = manager.or2(a_id, b_id);
    BDD_ID canonical_or_ab = manager.ite(a_id, TRUE_ID, b_id);

    // CRITICAL CHECK: Must match the canonical ITE result.
    EXPECT_EQ(or_ab_id, canonical_or_ab)<< "OR result must match the canonical ITE(a, True, b) node.";;
}

// --- Phase 4: Test Case 4 (XOR) ---
TEST_F(ManagerTest, XOR2) {
    std::cout << "\n--- Test_XOR2 ---" << std::endl;
    // SETUP: Create two variables
    BDD_ID a_id = manager.createVar("a"); // ID 2
    BDD_ID b_id = manager.createVar("b"); // ID 3

    EXPECT_EQ(manager.xor2(FALSE_ID, FALSE_ID), FALSE_ID) << "False XOR False must be False.";
    EXPECT_EQ(manager.xor2(TRUE_ID, FALSE_ID), TRUE_ID) << "True XOR False must be True.";;
    EXPECT_EQ(manager.xor2(FALSE_ID, TRUE_ID), TRUE_ID)<< "False XOR True must be True.";;
    EXPECT_EQ(manager.xor2(TRUE_ID, TRUE_ID), FALSE_ID)<< "True XOR True must be False.";;


    // Check Variable OR
    BDD_ID xor_ab_id = manager.xor2(a_id, b_id);
    BDD_ID canonical_xor_ab = manager.ite(a_id, manager.neg(b_id), b_id);

    // CRITICAL CHECK: Must match the canonical ITE result.
    EXPECT_EQ(xor_ab_id, canonical_xor_ab)<< "xOR result must match the canonical ITE(a, True, b) node.";;
}

// --- Phase 4: Test Case 5 (NAND, NOR, XNOR) ---
TEST_F(ManagerTest, NAND2) {
    // Note: These should be tested using combinations of the core functions.
    BDD_ID a_id = manager.createVar("a");
    BDD_ID b_id = manager.createVar("b");

    // NAND (NOT AND)
    std::cout << "\n--- Test_NAND2 ---" << std::endl;
    BDD_ID nand_result = manager.nand2(a_id, b_id);
    EXPECT_EQ(nand_result, manager.neg(manager.and2(a_id, b_id)));

}

TEST_F(ManagerTest, NOR2) {
    // Note: These should be tested using combinations of the core functions.
    BDD_ID a_id = manager.createVar("a");
    BDD_ID b_id = manager.createVar("b");

    // NOR (NOT OR)
    std::cout << "\n--- Test_NOR2 ---" << std::endl;
    BDD_ID nor_result = manager.nor2(a_id, b_id);
    EXPECT_EQ(nor_result, manager.neg(manager.or2(a_id, b_id)));

}


TEST_F(ManagerTest, XNOR2) {
    // Note: These should be tested using combinations of the core functions.
    BDD_ID a_id = manager.createVar("a");
    BDD_ID b_id = manager.createVar("b");

    // XNOR (NOT XOR)
    std::cout << "\n--- Test_XNOR2 ---" << std::endl;
    BDD_ID xnor_result = manager.xnor2(a_id, b_id);
    EXPECT_EQ(xnor_result, manager.neg(manager.xor2(a_id, b_id)));
}


TEST_F(ManagerTest, CoFactor_SimpleReduction) {
    std::cout << "\n--- Test_CofactorsSimpleReduction ---" << std::endl;
    BDD_ID a_id = manager.createVar("a"); // ID 2
    BDD_ID b_id = manager.createVar("b"); // ID 3

    // Function F = a OR b (ITE(a, True, b))
    BDD_ID f_id = manager.or2(a_id, b_id);

    // 1. Co-Factor True w.r.t. 'a' (F_a = True)
    // The result should be equivalent to: ITE(True, True, b) = True
    BDD_ID f_a_true = manager.coFactorTrue(f_id, a_id);
    EXPECT_EQ(f_a_true, TRUE_ID) << "CoFactorTrue(a OR b, a) must reduce to True.";

    // 2. Co-Factor False w.r.t. 'a' (F_not_a = b)
    // The result should be equivalent to: ITE(False, True, b) = b
    BDD_ID f_a_false = manager.coFactorFalse(f_id, a_id);
    EXPECT_EQ(f_a_false, b_id) << "CoFactorFalse(a OR b, a) must reduce to b.";

    // 3. Test CoFactor without specifying variable (should use topVar)
    // The topVar of F is 'a'.
    EXPECT_EQ(manager.coFactorTrue(f_id), TRUE_ID) << "CoFactorTrue(F) must use topVar 'a'.";
}


// --- Phase 5: Test Case 2 (Find All Nodes) ---
TEST_F(ManagerTest, FindNodes_ReturnsAllUniqueIDs) {
    std::cout << "\n--- Test_FindNodes ---" << std::endl;
    // SETUP: Create a complex BDD (e.g., F = a AND b)
    BDD_ID a_id = manager.createVar("a"); // ID 2
    BDD_ID b_id = manager.createVar("b"); // ID 3
    BDD_ID and_ab_id = manager.and2(a_id, b_id); // ID 4

    // The expected IDs are: 0 (False), 1 (True),  3 (b), 4 (a AND b). Total 4 nodes.
    std::set<BDD_ID> nodes;
    manager.findNodes(and_ab_id, nodes);

    EXPECT_TRUE(nodes.count(and_ab_id));
    EXPECT_FALSE(nodes.count(a_id)) << "Node 'a' (ID 2) is the topVar, but not a successor, and should NOT be counted.";
    EXPECT_TRUE(nodes.count(b_id));
    EXPECT_TRUE(nodes.count(FALSE_ID));
    EXPECT_TRUE(nodes.count(TRUE_ID));

    EXPECT_EQ(nodes.size(), 4) << "Must find all 4 unique nodes in the structure.";;

}

// --- Phase 5: Test Case 3 (Find All Variables) ---
TEST_F(ManagerTest, FindVars_ReturnsAllVariables) {
    std::cout << "\n--- Test_FindVars ---" << std::endl;
    // SETUP: Use the same complex BDD (F = a AND b)
    BDD_ID a_id = manager.createVar("a"); // ID 2
    BDD_ID b_id = manager.createVar("b"); // ID 3
    BDD_ID and_ab_id = manager.and2(a_id, b_id); // ID 4

    // The expected IDs are: 2 (a) and 3 (b). Total 2 variables.
    std::set<BDD_ID> vars;
    manager.findVars(and_ab_id, vars);

    // 1. Check size
    EXPECT_EQ(vars.size(), 2) << "Must find the 2 variables (a and b) used in the function.";

    // 2. Check content
    EXPECT_TRUE(vars.count(a_id));
    EXPECT_TRUE(vars.count(b_id));
    EXPECT_FALSE(vars.count(FALSE_ID)) << "Constants must not be included.";
    EXPECT_FALSE(vars.count(and_ab_id)) << "Complex nodes must not be included.";
}




//Simple test to see the graphics, not for the systems' functionality.
#include <fstream>

TEST_F(ManagerTest, Visualization_GeneratesDotFile) {
    // We create a few variables to make the graph interesting
    BDD_ID a = manager.createVar("a");
    BDD_ID b = manager.createVar("b");


    // WE tried with: BDD_ID f = manager.xor2(a, b);
    BDD_ID root_node = manager.xor2(a, b);;

    std::string filepath = "graph_test.dot";

    // then by call the visualize function, we test the visualizeBDD function
    manager.visualizeBDD(filepath, root_node);

    // It checks if the file exists and opens
    std::ifstream file(filepath);
    ASSERT_TRUE(file.is_open()) << "Error: The .dot file was not created.";

    // to make sure that it looks like a DOT file
    std::string first_line;
    std::getline(file, first_line);
    EXPECT_EQ(first_line, "digraph BDD {") << "Error: File content does not start with standard DOT header.";

    file.close();
}


// --- Phase 5: Test Case 4 (Ultimate Integration Test) ---
TEST_F(ManagerTest, IntegrationTest_ComplexExpressionMatchesSpecification) {
    // 1. SETUP: Create variables in the required order
    // Order: a (ID 2) > b (ID 3) > c (ID 4) > d (ID 5)
    BDD_ID a_id = manager.createVar("a");
    BDD_ID b_id = manager.createVar("b");
    BDD_ID c_id = manager.createVar("c");
    BDD_ID d_id = manager.createVar("d");

    EXPECT_EQ(a_id, 2) ;
    EXPECT_EQ(d_id, 5) ;
    // 2. Compute the sub-functions, verifying intermediate results against Tab. 2

    // F1 = a + b (ID 6 in the spec)
    BDD_ID F1_or_id = manager.or2(a_id, b_id);
    EXPECT_EQ(F1_or_id, 6) ;

    // F2 = c * d (ID 7 in the spec)
    BDD_ID F2_and_id = manager.and2(c_id, d_id);
    EXPECT_EQ(F2_and_id, 7) ;

    // 3. Compute the final function: F = F1 * F2 = (a+b) * (c*d)
    BDD_ID final_f_id = manager.and2(F1_or_id, F2_and_id);


    // 4. CRITICAL CHECKS (Comparing final result against the specification)

    // A. Check the FINAL BDD ID (Final function F is ID 9 in the spec)
    // You will need to check your unique table size count. Based on the spec (Tab. 2),
    // the final node ID should be the 10th entry, meaning ID 9.
    // NOTE: This check depends on your exact implementation matching the spec's order.
    EXPECT_EQ(final_f_id, 9) << "The final complex function ID must match the spec's final node ID (9).";

    // B. Check the FINAL UNIQUE TABLE SIZE
    // Tab. 2 shows the final unique table has 10 entries (ID 0 to ID 9).
    EXPECT_EQ(manager.uniqueTableSize(), 10) << "The total unique table size must match the spec (10 nodes).";

    // C. Optional: Check the topVar of the final node (should be 'a', ID 2)
    EXPECT_EQ(manager.topVar(final_f_id), a_id) << "The final top variable must be 'a'.";


    std::string filepath = "complex_integration.dot";

    manager.visualizeBDD(filepath, final_f_id);

}

// main function for tests (typically handled by main_test.cpp or gtest setup)
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}