# Proximity Search using 2D Range Trees

This project implements a spatial search algorithm using a 2D Range Tree for proximity queries based on **Chebyshev distance**. Inspired by the search functionality of mapping services like Google Maps, it enables efficient querying of points (e.g., restaurants) within a given square region.

---

## 🚀 Features

- **Efficient Tree Construction**: O(n log n)
- **Fast Querying**: O(m + (log n)²) per query
- **Chebyshev Distance Support**: Square-like search radius
- **Handles Large Data**: Optimized for 10,000+ points

---

## 🧠 Algorithms Used

- **2D Range Tree** with a secondary structure sorted by Y-coordinate.
- **Chebyshev Distance Filtering** during queries.

---

## 📦 Example Usage

**Input:**
Enter number of restaurants: 5
Enter the coordinates (x y) of each restaurant:
1 2
3 4
5 6
7 8
9 10
Enter reference point (x y): 4 4
Enter Chebyshev distance: 2

**Output:**
Restaurants within Chebyshev distance 2 of (4, 4):
Total: 2 restaurant(s)
(3, 4)
(5, 6)
