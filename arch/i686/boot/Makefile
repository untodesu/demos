sources_y += pgdir.S
sources_y += start.S

clean_list_y += pgdir.S

$(TREE)/pgdir.S: ./scripts/x86-mkpgdir.sh
	./scripts/x86-mkpgdir.sh -n $(CONFIG_MEM_PAGE_TABS) > $@
