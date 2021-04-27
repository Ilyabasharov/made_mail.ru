import os
import matplotlib.pyplot as plt
from prettytable import PrettyTable
from IPython.display import clear_output
from collections import defaultdict

class Collector:
    
    def __init__(
        self,
        root_graphics: str,
        root_desc: str,
        phases,
    ) -> None:
        
        os.makedirs(root_graphics, exist_ok=True)
        os.makedirs(root_desc, exist_ok=True)
        
        self.tables = defaultdict(dict)
        
        for phase in phases:
            self.tables[phase]['table'] = PrettyTable()
            self.tables[phase]['table'].field_names = ['epoch', '%s %s' % (phase, 'loss')]
            self.tables[phase]['path'] = os.path.join(root_desc, '%s.txt' % phase)
        
        self.path_graphics = os.path.join(root_graphics, 'metrics.jpg')
        
    def step(
        self,
        data: dict,
    ) -> None:
        
        clear_output(True)
        
        for phase in data:
            self.tables[phase]['table'].add_row([len(data[phase]), data[phase][-1]])
            plt.plot(data[phase], label=phase)
            
            with open(self.tables[phase]['path'], 'w') as file:
                file.write(self.tables[phase]['table'].get_string())
                
        plt.xlabel('epochs')
        plt.ylabel('loss')
        plt.legend()
        plt.grid()
        plt.savefig(self.path_graphics, format='jpg')
        plt.show()