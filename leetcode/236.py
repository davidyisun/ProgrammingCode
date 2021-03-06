# -*- coding: utf-8 -*-
# @Author: gunjianpan
# @Date:   2020-03-25 13:10:46
# @Last Modified by:   gunjianpan
# @Last Modified time: 2020-03-25 13:35:32

"""
236. Lowest Common Ancestor of a Binary Tree Medium

Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”

Given the following binary tree:  root = [3,5,1,6,2,0,8,null,null,7,4]

## Example 1:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.

## Example 2:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
 
## Note:
All of the nodes' values will be unique.
p and q are different and both values will exist in the binary tree.

Accepted 404,015 Submissions 940,316
"""
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None


class Solution:
    def lowestCommonAncestor(
        self, root: "TreeNode", p: "TreeNode", q: "TreeNode"
    ) -> "TreeNode":
        self.result = None

        def postorder(head: TreeNode) -> bool:
            if self.result is not None:
                return False
            if head.left is not None:
                left = postorder(head.left)
            else:
                left = False
            if head.right is not None:
                right = postorder(head.right)
            else:
                right = False
            # print(head.val, left, right, self.result)
            if head.val == p.val or head.val == q.val:
                if left or right:
                    if self.result is None:
                        self.result = head
                return True
            if left == True and right == True:
                if self.result is None:
                    self.result = head
            return left or right

        postorder(root)
        return self.result
