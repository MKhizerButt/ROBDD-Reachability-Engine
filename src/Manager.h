// // src/Manager.h
// // ... (includes and BDD_Node struct)
//     class Manager : public ManagerInterface {
//     public:
//         Manager();
//
//         // All functions must be declared here to avoid compiler warnings/errors
//         BDD_ID createVar(const std::string &label) override;
//         const BDD_ID &True() override;
//         const BDD_ID &False() override;
//         bool isConstant(BDD_ID f) override;
//         bool isVariable(BDD_ID x) override;
//         BDD_ID topVar(BDD_ID f) override; // <-- Needs implementation
//         BDD_ID ite(BDD_ID i, BDD_ID t, BDD_ID e) override; // <-- Needs implementation
//         BDD_ID coFactorTrue(BDD_ID f, BDD_ID x) override; // <-- Needs implementation
//         BDD_ID coFactorFalse(BDD_ID f, BDD_ID x) override; // <-- Needs implementation
//         BDD_ID coFactorTrue(BDD_ID f) override; // <-- Needs implementation
//         BDD_ID coFactorFalse(BDD_ID f) override; // <-- Needs implementation
//         BDD_ID and2(BDD_ID a, BDD_ID b) override; // <-- Needs implementation
//         BDD_ID or2(BDD_ID a, BDD_ID b) override; // <-- Needs implementation
//         BDD_ID xor2(BDD_ID a, BDD_ID b) override; // <-- Needs implementation
//         BDD_ID neg(BDD_ID a) override; // <-- Needs implementation
//         BDD_ID nand2(BDD_ID a, BDD_ID b) override; // <-- Needs implementation
//         BDD_ID nor2(BDD_ID a, BDD_ID b) override; // <-- Needs implementation
//         BDD_ID xnor2(BDD_ID a, BDD_ID b) override; // <-- Needs implementation
//         std::string getTopVarName(const BDD_ID &root) override; // <-- Needs implementation
//         void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) override; // <-- Needs implementation
//         void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) override; // <-- Needs implementation
//         size_t uniqueTableSize() override;
//         void visualizeBDD(std::string filepath, BDD_ID &root) override; // <-- Needs implementation
//
//         // ... (private members)
//     };
// }
//
// #ifndef VDSPROJECT_MANAGER_H
// #define VDSPROJECT_MANAGER_H
//
// #include "ManagerInterface.h"
// #include <vector>
// #include <string>
// #include <set>              // <--- THIS WAS MISSING
// #include <map>
// #include <iostream>
//
// namespace ClassProject {
//
//         struct BDDNode {
//             BDD_ID id;
//             BDD_ID high;
//             BDD_ID low;
//             BDD_ID topVar;
//             std::string label;
//         };
//
//         class Manager : public ManagerInterface {
//         private:
//             std::vector<BDDNode> nodes;
//             const BDD_ID FALSE_ID = 0;
//             const BDD_ID TRUE_ID = 1;
//
//         public:
//             Manager();
//
//             BDD_ID createVar(const std::string &label) override;
//
//             const BDD_ID &True() override;
//             const BDD_ID &False() override;
//
//             bool isConstant(BDD_ID f) override;
//             bool isVariable(BDD_ID x) override;
//             BDD_ID topVar(BDD_ID f) override;
//
//             BDD_ID ite(BDD_ID i, BDD_ID t, BDD_ID e) override;
//
//             BDD_ID coFactorTrue(BDD_ID f, BDD_ID x) override;
//             BDD_ID coFactorFalse(BDD_ID f, BDD_ID x) override;
//             BDD_ID coFactorTrue(BDD_ID f) override;
//             BDD_ID coFactorFalse(BDD_ID f) override;
//
//             BDD_ID and2(BDD_ID a, BDD_ID b) override;
//             BDD_ID or2(BDD_ID a, BDD_ID b) override;
//             BDD_ID xor2(BDD_ID a, BDD_ID b) override;
//             BDD_ID neg(BDD_ID a) override;
//             BDD_ID nand2(BDD_ID a, BDD_ID b) override;
//             BDD_ID nor2(BDD_ID a, BDD_ID b) override;
//             BDD_ID xnor2(BDD_ID a, BDD_ID b) override;
//
//             std::string getTopVarName(const BDD_ID &root) override;
//             void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) override;
//             void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) override;
//             size_t uniqueTableSize() override;
//             void visualizeBDD(std::string filepath, BDD_ID &root) override;
//         };
//     }
// #endif
////////////////////////////////////////////////////////


#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include <vector>
#include <string>
#include <set>
#include <map>

namespace ClassProject {

    struct BDDNode {
        BDD_ID id;
        BDD_ID high;
        BDD_ID low;
        BDD_ID topVar;
        std::string label;
    };

    class Manager : public ManagerInterface {
    private:
        std::vector<BDDNode> nodes;
        const BDD_ID FALSE_ID = 0;
        const BDD_ID TRUE_ID = 1;
        void visualizeNode(BDD_ID id, std::ostream &outputFile, std::set<BDD_ID> &visitedNodes);

    public:
        Manager();

        BDD_ID createVar(const std::string &label) override;
        const BDD_ID &True() override;
        const BDD_ID &False() override;
        bool isConstant(BDD_ID f) override;
        bool isVariable(BDD_ID x) override;
        BDD_ID topVar(BDD_ID f) override;
        BDD_ID ite(BDD_ID i, BDD_ID t, BDD_ID e) override;
        BDD_ID coFactorTrue(BDD_ID f, BDD_ID x) override;
        BDD_ID coFactorFalse(BDD_ID f, BDD_ID x) override;
        BDD_ID coFactorTrue(BDD_ID f) override;
        BDD_ID coFactorFalse(BDD_ID f) override;
        BDD_ID and2(BDD_ID a, BDD_ID b) override;
        BDD_ID or2(BDD_ID a, BDD_ID b) override;
        BDD_ID xor2(BDD_ID a, BDD_ID b) override;
        BDD_ID neg(BDD_ID a) override;
        BDD_ID nand2(BDD_ID a, BDD_ID b) override;
        BDD_ID nor2(BDD_ID a, BDD_ID b) override;
        BDD_ID xnor2(BDD_ID a, BDD_ID b) override;
        std::string getTopVarName(const BDD_ID &root) override;
        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) override;
        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) override;
        size_t uniqueTableSize() override;
        void visualizeBDD(std::string filepath, BDD_ID &root) override;
    };
}
#endif
