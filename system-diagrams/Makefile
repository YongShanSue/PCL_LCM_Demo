PROJ1 = assistive-robotics-sys
PROJ2 = rv-tag-text-sys

all:
	dot -Tpng $(PROJ1).dot -o $(PROJ1).png
	dot -Tsvg $(PROJ1).dot -o $(PROJ1).svg
	dot -Tpng $(PROJ2).dot -o $(PROJ2).png
	dot -Tsvg $(PROJ2).dot -o $(PROJ2).svg

clean:
	rm *.png *.svg
