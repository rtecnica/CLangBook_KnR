struct WordEntry {
    word: String,
    count: u32,
    pages: Vec<u32>,
}

impl WordEntry {

    pub fn new_from(word: String) -> WordEntry {
        return WordEntry {
            word,
            count: 1,
            pages: vec![],
        };
    }

    pub fn count(&mut self) {
        self.count += 1;
    }

    pub fn add_page(&mut self, page: u32) {
        let mut page_added = false;
        for old_page in self.pages.iter() {
            if old_page == &page {
                page_added = true;
            }
        }
        if !page_added {
            self.pages.push(page);
        }
    }

    pub fn compare_word_alph(&self, word: &WordEntry) -> i8 {
        let mut ctr = 0;
        for chartuple in self.word.chars().zip(word.word.chars()) {
            if chartuple.0 > chartuple.1 {
                ctr += 1;
            }
            if chartuple.0 < chartuple.1 {
                ctr -= 1;
            }
        }
        return ctr;
    }
}
