void Solver::restore(CPStore& cp, OpenNode nd)
{
    if (ToulBar2::verbose >= 1) {
        if (wcsp->getTreeDec()) {
            cout << "[C" << wcsp->getTreeDec()->getCurrentCluster()->getId() << "] restore open node " << nd.getCost(wcsp->getTreeDec()->getCurrentCluster()->getCurrentDelta()) << " (" << nd.first << ", " << nd.last << ")" << endl;
        } else {
            cout << "restore open node " << nd.getCost(MIN_COST) << " (" << nd.first << ", " << nd.last << ")" << endl;
        }
    }
    assert(nd.last >= nd.first);
    nbRecomputationNodes += nd.last - nd.first;

    ptrdiff_t maxsize = nd.last - nd.first;
    int assignLS[maxsize];
    Value valueLS[maxsize];
    unsigned int size = 0;
    for (ptrdiff_t idx = nd.first; idx < nd.last; ++idx) {
        assert((size_t)idx < cp.size());
        assert(!wcsp->getTreeDec() || wcsp->getTreeDec()->getCurrentCluster()->isVar(cp[idx].varIndex));
        if ((cp[idx].op == CP_ASSIGN && !(cp[idx].reverse && idx < nd.last - 1)) || (cp[idx].op == CP_REMOVE && cp[idx].reverse && idx < nd.last - 1)) {
            assignLS[size] = cp[idx].varIndex;
            valueLS[size] = cp[idx].value;
            size++;
        }
    }
    wcsp->enforceUb();
    wcsp->assignLS(assignLS, valueLS, size, false); // fast multiple assignments
    for (ptrdiff_t idx = nd.first; idx < nd.last; ++idx) {
        assert((size_t)idx < cp.size());
        if (ToulBar2::verbose >= 1)
            cout << "retrieve choice point " << CPOperation[cp[idx].op] << ((cp[idx].reverse) ? "*" : "") << " (" << wcsp->getName(cp[idx].varIndex) << ", " << cp[idx].value << ") at position " << idx << endl;
        if (ToulBar2::verbose >= 1)
            cout << *((WCSP*)wcsp)->getVar(cp[idx].varIndex) << endl;
        nbNodes++;
        switch (cp[idx].op) { //TODO: some operations (remove,increase,decrease) are useless because of all assigns previously done
        case CP_ASSIGN: {
            if (cp[idx].reverse && idx < nd.last - 1) {
                wcsp->remove(cp[idx].varIndex, cp[idx].value);
                addChoicePoint(CP_REMOVE, cp[idx].varIndex, cp[idx].value, false);
            } else
                addChoicePoint(CP_ASSIGN, cp[idx].varIndex, cp[idx].value, false);
            break;
        }
        case CP_REMOVE: {
            if (cp[idx].reverse && idx < nd.last - 1) {
                addChoicePoint(CP_ASSIGN, cp[idx].varIndex, cp[idx].value, false);
            } else {
                wcsp->remove(cp[idx].varIndex, cp[idx].value);
                addChoicePoint(CP_REMOVE, cp[idx].varIndex, cp[idx].value, false);
            }
            break;
        }
        case CP_INCREASE: {
            if (cp[idx].reverse && idx < nd.last - 1) {
                wcsp->decrease(cp[idx].varIndex, cp[idx].value - 1);
                addChoicePoint(CP_DECREASE, cp[idx].varIndex, cp[idx].value - 1, false);
            } else {
                wcsp->increase(cp[idx].varIndex, cp[idx].value);
                addChoicePoint(CP_INCREASE, cp[idx].varIndex, cp[idx].value, false);
            }
            break;
        }
        case CP_DECREASE: {
            if (cp[idx].reverse && idx < nd.last - 1) {
                wcsp->increase(cp[idx].varIndex, cp[idx].value + 1);
                addChoicePoint(CP_INCREASE, cp[idx].varIndex, cp[idx].value + 1, false);
            } else {
                wcsp->decrease(cp[idx].varIndex, cp[idx].value);
                addChoicePoint(CP_DECREASE, cp[idx].varIndex, cp[idx].value, false);
            }
            break;
        }
        default: {
            cerr << "unknown choice point for hybrid best first search!!!" << endl;
            exit(EXIT_FAILURE);
        }
        }
    }
    wcsp->propagate();
    //if (wcsp->getLb() != nd.getCost(((wcsp->getTreeDec())?wcsp->getTreeDec()->getCurrentCluster()->getCurrentDelta():MIN_COST))) cout << "***** node cost: " << nd.getCost(((wcsp->getTreeDec())?wcsp->getTreeDec()->getCurrentCluster()->getCurrentDelta():MIN_COST)) << " but lb: " << wcsp->getLb() << endl;
}
