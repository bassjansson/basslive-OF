#pragma once

#include "BL_Core.h"

namespace BassLive
{
    template<class T>
    class Node
    {
    public:
        //================================================================
        ~Node()
        {
            UInt size = (UInt)connectedNodes.size();

            for (UInt i = 0; i < size; ++i)
                eraseFirstMatchingNodeFrom(connectedNodes[i]->connectedNodes, this);

            connectedNodes.clear();
        }

        //================================================================
        void connectTo(Node<T>& node)
        {
            Node<T>* nodePtr = &node;

            if (nodePtr == this)
                return;

            UInt size = (UInt)connectedNodes.size();

            for (UInt i = 0; i < size; ++i)
                if (connectedNodes[i] == nodePtr)
                    return;

            connectedNodes.push_back(nodePtr);
            node.connectedNodes.push_back(this);
        }

        void disconnectFrom(Node<T>& node)
        {
            Node<T>* nodePtr = &node;

            if (nodePtr == this)
                return;

            eraseFirstMatchingNodeFrom(connectedNodes, nodePtr);
            eraseFirstMatchingNodeFrom(node.connectedNodes, this);
        }

        //================================================================
        UInt numberOfConnectedNodes() const
        {
            return connectedNodes.size();
        }

        const T& getValueOfConnectedNode(UInt i) const
        {
            return (i < connectedNodes.size()) ? connectedNodes[i]->nodeValue : nodeValue;
        }

        T& value()
        {
            return nodeValue;
        }
        
    private:
        //================================================================
        void eraseFirstMatchingNodeFrom(vector<Node<T>*>& nodes, const Node<T>* nodeToMatch)
        {
            UInt size = (UInt)nodes.size();

            for (UInt i = 0; i < size; ++i)
            {
                if (nodes[i] == nodeToMatch)
                {
                    nodes.erase(nodes.begin() + i);
                    return;
                }
            }
        }

        //================================================================
        vector<Node<T>*> connectedNodes;
        T nodeValue;
    };
}
