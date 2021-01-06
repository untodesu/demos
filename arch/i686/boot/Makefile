sources_y += pgdir.S
sources_y += start.S

clean_list_y += pgdir.S

$(TREE)/pgdir.S: ./scripts/i686-genpgdir.sh
	./scripts/i686-genpgdir.sh -n $(CONFIG_PAGE_TABLES) > $@
