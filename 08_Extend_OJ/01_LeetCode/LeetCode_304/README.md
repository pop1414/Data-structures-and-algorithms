# 303. 区域和检索 - 数组不可变

**难度：简单**
**相关标签：数组、前缀和**
**相关企业：算法面试高频题**

---

## 题目描述

给定一个整数数组 `nums`，处理以下类型的多个查询：

1. 计算索引 `left` 和 `right`（包含 `left` 和 `right`）之间的 `nums` 元素的和，其中 `left <= right`

实现 `NumArray` 类：

- `NumArray(int[] nums)`：使用数组 `nums` 初始化对象
- `int sumRange(int left, int right)`：返回数组 `nums` 中索引 `left` 和 `right` 之间的元素总和，包含 `left` 和 `right` 两点（即 `nums[left] + nums[left+1] + ... + nums[right]`）

---

## 示例 1

**输入：**

```
["NumArray", "sumRange", "sumRange", "sumRange"]
[[-2, 0, 3, -5, 2, -1], [0, 2], [2, 5], [0, 5]]
```

**输出：**

```
[null, 1, -1, -3]
```

**解释：**

```java
NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
numArray.sumRange(0, 2); // 返回 1 ((-2) + 0 + 3)
numArray.sumRange(2, 5); // 返回 -1 (3 + (-5) + 2 + (-1))
numArray.sumRange(0, 5); // 返回 -3 ((-2) + 0 + 3 + (-5) + 2 + (-1))
```

---

## 提示

- `1 <= nums.length <= 10^4`
- `-10^5 <= nums[i] <= 10^5`
- `0 <= left <= right < nums.length`
- 最多调用 `10^4` 次 `sumRange` 方法

---

## 解题思路（前缀和优化）

### 核心思想

通过**预处理前缀和数组**，将单次 `sumRange` 查询的时间复杂度从 O(n) 优化到 O(1)：

- 前缀和数组 `preSum` 中，`preSum[i]` 表示 `nums[0]` 到 `nums[i-1]` 的累加和。
- 区间 `[left, right]` 的和 = `preSum[right+1] - preSum[left]`。

---

## 复杂度分析

- **时间复杂度**：
    - 初始化：O(n)，遍历一次数组构建前缀和。
    - `sumRange`：O(1)，直接通过前缀和数组计算区间和。
- **空间复杂度**：O(n)，需要额外存储前缀和数组。

---
