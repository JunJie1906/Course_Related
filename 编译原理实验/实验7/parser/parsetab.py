
# parsetab.py
# This file is automatically generated. Do not edit.
# pylint: disable=W,C,R
_tabversion = '3.10'

_lr_method = 'LALR'

_lr_signature = 'AND AS AVG BETWEEN BY COMMA COUNT DOT FROM IN LP MAX MIN NAME NUMBER OR ORDER RP SELECT STAR SUM WHERE cmp literalsquery :  select\n             | LP query RP\n    select :  SELECT list FROM table WHERE lst ORDER BY list\n       | SELECT list FROM table WHERE lst\n       | SELECT list FROM table ORDER BY list\n       | SELECT list FROM table\n    \n    table :  NAME\n       | LP query RP\n       | table COMMA table\n    \n    lst : condition\n       | condition AND condition\n       | condition OR condition\n       | NAME BETWEEN NUMBER AND NUMBER\n       | NAME IN LP query RP\n       | NAME literals agg\n       | agg literals NUMBER\n condition : NAME cmp NUMBER\n                  \n    agg : SUM LP NAME RP\n         | AVG LP NAME RP\n         | COUNT LP NAME RP\n         | MIN LP NAME RP\n         | MAX LP NAME RP\n\n    list : STAR\n         | NAME\n         | NAME DOT NAME\n         | list COMMA list\n         | list AND NAME\n         | list OR NAME\n        | NAME AS NAME\n        | list AS NAME\n         | agg\n'
    
_lr_action_items = {'LP':([0,3,10,11,12,13,14,16,30,44,62,72,],[3,3,23,24,25,26,27,30,3,30,72,3,]),'SELECT':([0,3,30,72,],[4,4,4,4,]),'$end':([1,2,7,8,9,15,28,29,31,32,33,34,35,36,46,47,48,49,50,51,52,56,57,66,68,70,73,74,75,76,79,80,],[0,-1,-23,-24,-31,-2,-6,-7,-26,-27,-28,-30,-25,-29,-18,-19,-20,-21,-22,-4,-10,-9,-8,-5,-11,-12,-15,-17,-16,-3,-13,-14,]),'RP':([2,5,7,8,9,15,28,29,31,32,33,34,35,36,37,38,39,40,41,45,46,47,48,49,50,51,52,56,57,66,68,70,73,74,75,76,78,79,80,],[-1,15,-23,-24,-31,-2,-6,-7,-26,-27,-28,-30,-25,-29,46,47,48,49,50,57,-18,-19,-20,-21,-22,-4,-10,-9,-8,-5,-11,-12,-15,-17,-16,-3,80,-13,-14,]),'STAR':([4,17,55,67,],[7,7,7,7,]),'NAME':([4,16,17,18,19,20,21,22,23,24,25,26,27,42,44,55,59,60,67,],[8,29,8,32,33,34,35,36,37,38,39,40,41,53,29,8,69,69,8,]),'SUM':([4,17,42,55,63,67,],[10,10,10,10,10,10,]),'AVG':([4,17,42,55,63,67,],[11,11,11,11,11,11,]),'COUNT':([4,17,42,55,63,67,],[12,12,12,12,12,12,]),'MIN':([4,17,42,55,63,67,],[13,13,13,13,13,13,]),'MAX':([4,17,42,55,63,67,],[14,14,14,14,14,14,]),'FROM':([6,7,8,9,31,32,33,34,35,36,46,47,48,49,50,],[16,-23,-24,-31,-26,-27,-28,-30,-25,-29,-18,-19,-20,-21,-22,]),'COMMA':([6,7,8,9,28,29,31,32,33,34,35,36,46,47,48,49,50,56,57,66,76,],[17,-23,-24,-31,44,-7,17,-27,-28,-30,-25,-29,-18,-19,-20,-21,-22,44,-8,17,17,]),'AND':([6,7,8,9,31,32,33,34,35,36,46,47,48,49,50,52,66,71,74,76,],[18,-23,-24,-31,18,-27,-28,-30,-25,-29,-18,-19,-20,-21,-22,59,18,77,-17,18,]),'OR':([6,7,8,9,31,32,33,34,35,36,46,47,48,49,50,52,66,74,76,],[19,-23,-24,-31,19,-27,-28,-30,-25,-29,-18,-19,-20,-21,-22,60,19,-17,19,]),'AS':([6,7,8,9,31,32,33,34,35,36,46,47,48,49,50,66,76,],[20,-23,22,-31,20,-27,-28,-30,-25,-29,-18,-19,-20,-21,-22,20,20,]),'DOT':([8,],[21,]),'WHERE':([28,29,56,57,],[42,-7,-9,-8,]),'ORDER':([28,29,46,47,48,49,50,51,52,56,57,68,70,73,74,75,79,80,],[43,-7,-18,-19,-20,-21,-22,58,-10,-9,-8,-11,-12,-15,-17,-16,-13,-14,]),'BY':([43,58,],[55,67,]),'literals':([46,47,48,49,50,53,54,],[-18,-19,-20,-21,-22,63,65,]),'BETWEEN':([53,],[61,]),'IN':([53,],[62,]),'cmp':([53,69,],[64,64,]),'NUMBER':([61,64,65,77,],[71,74,75,79,]),}

_lr_action = {}
for _k, _v in _lr_action_items.items():
   for _x,_y in zip(_v[0],_v[1]):
      if not _x in _lr_action:  _lr_action[_x] = {}
      _lr_action[_x][_k] = _y
del _lr_action_items

_lr_goto_items = {'query':([0,3,30,72,],[1,5,45,78,]),'select':([0,3,30,72,],[2,2,2,2,]),'list':([4,17,55,67,],[6,31,66,76,]),'agg':([4,17,42,55,63,67,],[9,9,54,9,73,9,]),'table':([16,44,],[28,56,]),'lst':([42,],[51,]),'condition':([42,59,60,],[52,68,70,]),}

_lr_goto = {}
for _k, _v in _lr_goto_items.items():
   for _x, _y in zip(_v[0], _v[1]):
       if not _x in _lr_goto: _lr_goto[_x] = {}
       _lr_goto[_x][_k] = _y
del _lr_goto_items
_lr_productions = [
  ("S' -> query","S'",1,None,None,None),
  ('query -> select','query',1,'p_query','t.py',123),
  ('query -> LP query RP','query',3,'p_query','t.py',124),
  ('select -> SELECT list FROM table WHERE lst ORDER BY list','select',9,'p_select','t.py',133),
  ('select -> SELECT list FROM table WHERE lst','select',6,'p_select','t.py',134),
  ('select -> SELECT list FROM table ORDER BY list','select',7,'p_select','t.py',135),
  ('select -> SELECT list FROM table','select',4,'p_select','t.py',136),
  ('table -> NAME','table',1,'p_table','t.py',159),
  ('table -> LP query RP','table',3,'p_table','t.py',160),
  ('table -> table COMMA table','table',3,'p_table','t.py',161),
  ('lst -> condition','lst',1,'p_lst','t.py',178),
  ('lst -> condition AND condition','lst',3,'p_lst','t.py',179),
  ('lst -> condition OR condition','lst',3,'p_lst','t.py',180),
  ('lst -> NAME BETWEEN NUMBER AND NUMBER','lst',5,'p_lst','t.py',181),
  ('lst -> NAME IN LP query RP','lst',5,'p_lst','t.py',182),
  ('lst -> NAME literals agg','lst',3,'p_lst','t.py',183),
  ('lst -> agg literals NUMBER','lst',3,'p_lst','t.py',184),
  ('condition -> NAME cmp NUMBER','condition',3,'p_condition','t.py',214),
  ('agg -> SUM LP NAME RP','agg',4,'p_agg','t.py',225),
  ('agg -> AVG LP NAME RP','agg',4,'p_agg','t.py',226),
  ('agg -> COUNT LP NAME RP','agg',4,'p_agg','t.py',227),
  ('agg -> MIN LP NAME RP','agg',4,'p_agg','t.py',228),
  ('agg -> MAX LP NAME RP','agg',4,'p_agg','t.py',229),
  ('list -> STAR','list',1,'p_list','t.py',248),
  ('list -> NAME','list',1,'p_list','t.py',249),
  ('list -> NAME DOT NAME','list',3,'p_list','t.py',250),
  ('list -> list COMMA list','list',3,'p_list','t.py',251),
  ('list -> list AND NAME','list',3,'p_list','t.py',252),
  ('list -> list OR NAME','list',3,'p_list','t.py',253),
  ('list -> NAME AS NAME','list',3,'p_list','t.py',254),
  ('list -> list AS NAME','list',3,'p_list','t.py',255),
  ('list -> agg','list',1,'p_list','t.py',256),
]
