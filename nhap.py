from abc import ABC, abstractmethod

class Animal():
    def __init__(self,khoga,qnt):
        self._food = khoga
        self._npc = qnt 
    def real_npc(self):
        print(self.npc)

mixi = Animal("khogadetem","qnt")
print(mixi.real_npc)
