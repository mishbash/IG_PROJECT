#include "ig.h"

#include <ranges>
#include <string>

IGNode::IGNode() : children(0), negate(0), func(0) {}

IGNode::IGNode(std::vector<unsigned> children, std::vector<bool> negate, std::vector<bool> values) : 
    children(children), negate(negate), func(values) {}

void IGNode::connect(unsigned child, bool neg) {
    children.push_back(child);
    negate.push_back(neg);
}

IG::IG() : variable_count(5), output(0), negate_output(false), nodes() {}

IG::~IG() {}


unsigned IG::addNode(const IGNode &node) {
    nodes.push_back(node);
    return nodes.size() + variable_count;
}

bool IG::hasCycles() const {
    // std::vector<unsigned> used(nodes.size());
    // return traverse_cycles(output, used);
    return false;
}

bool IG::traverse(const std::vector<bool>& x, unsigned v, std::vector<bool>& used, std::vector<bool>& used_res) const {
    if ((v >= 1) && (v <= variable_count)) {
        return !x[v - 1];
    }
    v -= variable_count + 1;
    if (used[v]) {
        return used_res[v];
    }
    used[v] = true;

    // check if children != function inputs
    auto node = nodes[v];
    std::vector<bool> t_table(node.children.size(), 0);

    for (int i = 0; auto child : node.children) {
        t_table[i] = traverse(x, child, used, used_res) ^ node.negate[i];
        ++i;
    }

    return used_res[v] = node.func.getValue(t_table);
}


Function IG::getFunction() const {
    std::vector<bool> x(variable_count, false);
    Function f(variable_count);
    for (unsigned i = 0; i < (1 << variable_count); ++i) {
        std::vector<bool> used(nodes.size(), 0);
        std::vector<bool> used_res(nodes.size(), 0);
        bool value = traverse(x, output, used, used_res) ^ negate_output;
        f.setValue(x, value);
        for (int j = (variable_count - 1); j >= 0; --j) {
            x[j] = !x[j];
            if (x[j]) {
                break;
            }
        }
    }
    return f;
}


void IG::read(std::istream &istream) {
    nodes.clear();
    unsigned cmplx;
    istream >> cmplx >> output >> negate_output;
    for (unsigned i = 0; i < cmplx; ++i) {
        IGNode node;

        unsigned node_amount;
        istream >> node_amount;

        for (auto k : std::views::iota(0u, node_amount)) {
            unsigned new_node;
            bool new_node_negate;
            istream >> new_node >> new_node_negate;
            node.connect(new_node, new_node_negate);
        }

        std::vector<bool> new_node_function(1 << node_amount);
        std::string s;
        istream >> s;

        for (auto [index, value] : std::views::enumerate(new_node_function)) {
            value = s[index] == '1';
        }
        

        node.func = Function(new_node_function);

        nodes.push_back(node);
    }
}

void IG::print(std::ostream &ostream) const {
    ostream << getComplexity() << "\n";
    ostream << output << " " << (negate_output ? 1 : 0) << "\n\n";

    int count = variable_count + 1;
    for (auto& ig_node : nodes) {
        ostream << "Node #" << count << "\n";
        ostream << "Connected:\n";
        for (const auto& c : ig_node.children) {
            ostream << c << " ";
        }
        ostream << "\nNegate:\n";
        for (const auto& n : ig_node.negate) {
            ostream << n << " ";
        }
        ostream << "\nFunction\n";
        ig_node.func.print(ostream);
        ostream << "\n";
        ++count;
    }
}

unsigned IG::getVariableCount() const {
    return variable_count;
}

void IG::setVariableCount(unsigned count) {
    variable_count = count;
}

unsigned IG::getOutput() const {
    return output;
}

void IG::setOutput(unsigned vertex) {
    output = vertex;
}

bool IG::getNegateOutput() const {
    return negate_output;
}

void IG::setNegateOutput(bool value) {
    negate_output = value;
}

std::vector<IGNode> &IG::getNodes() {
    return nodes;
}

const std::vector<IGNode> &IG::getNodes() const {
    return nodes;
}

unsigned IG::getComplexity() const {
    return nodes.size();
}






/*



[1][2][3][][][][][][][][][][]


      [1]
      /\
   [2] [3]
  /\    /\
[4][5][6][7]




       [1]
      /  \
   [2]   [3]
        / | \
      [4][5][6]




*/