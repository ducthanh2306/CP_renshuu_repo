class EmptyClass:
    pass
---------------------------------------------------
class Website:
    def __init__(self, address):
        self.address = address
    
    def display_address(self):
        print("Địa chỉ website:", self.address)

# Tạo đối tượng
site = Website("https://example.com")
site.display_address()
----------------------------------------------------
import math

class Circle:
    def __init__(self, radius):
        self.radius = radius
    
    def circumference(self):
        return 2 * math.pi * self.radius
    
    def area(self):
        return math.pi * self.radius ** 2

------------------------------------------------
# Test
c = Circle(5)
print("Chu vi:", c.circumference())
print("Diện tích:", c.area())

class Rectangle:
    def __init__(self, length, width):
        self.length = length
        self.width = width
    
    def perimeter(self):
        return 2 * (self.length + self.width)
    
    def area(self):
        return self.length * self.width


# Test
r = Rectangle(4, 3)
print("Chu vi:", r.perimeter())
print("Diện tích:", r.area())