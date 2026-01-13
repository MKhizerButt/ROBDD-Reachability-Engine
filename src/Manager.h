#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include <vector>
#include <string>
#include <set>
#include <unordered_map>

namespace ClassProject {
    struct BDDNode {
        //BDD_ID id;
        BDD_ID high;
        BDD_ID low;
        BDD_ID topVar;
        std::string label;
    };

    struct ComputedKey {
        BDD_ID i, t, e;

        // Equality check for collision , ite is new key, other is old key
        bool operator==(const ComputedKey &other) const {
            return (i == other.i && t == other.t && e == other.e);
        }
    };

    struct UniqueKey {
        BDD_ID high, low, topVar;

        bool operator==(const UniqueKey &other) const {
            return (high == other.high && low == other.low && topVar == other.topVar);
        }
    };

    struct KeyHasher {
        // Decides buckets using primes - Functor
        size_t operator()(const ComputedKey &k) const {
            return k.i + (k.t * 31) + (k.e * 31 * 31);
        }

        size_t operator()(const UniqueKey &k) const {
            return k.high + (k.low * 31) + (k.topVar * 31 * 31);
        }
    };

    class Manager : public ManagerInterface {
    private:
        std::vector<BDDNode> nodes;
        const BDD_ID FALSE_ID = 0;
        const BDD_ID TRUE_ID = 1;

        void visualizeNode(BDD_ID id, std::ostream &outputFile, std::set<BDD_ID> &visitedNodes);

        // we specify the map as: Container <Key, Value, Hasher> name;

        // The Cache: Prevents recalculating the recursion in ite
        std::unordered_map<ComputedKey, BDD_ID, KeyHasher> computedTable;

        // The Nodefinder: Such that nodes are reused if already existing/For Canonicity
        std::unordered_map<UniqueKey, BDD_ID, KeyHasher> uniqueTable;

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
