use std::fmt;

#[derive(Debug)]
pub struct WordEntry {
    word: String,
    count: u32,
    pages: Vec<u32>,
}

impl WordEntry {
    pub fn new_from(word: &str, page: &u32) -> WordEntry {
        WordEntry {
            word: word.to_string(),
            count: 1,
            pages: vec![*page],
        }
    }

    pub fn count(&mut self) {
        self.count += 1;
    }

    pub fn add_page(&mut self, page: u32) {
        let mut page_added = false;
        for old_page in &self.pages {
            if old_page == &page {
                page_added = true;
            }
        }
        if !page_added {
            self.pages.push(page);
        }
    }

    pub fn compare_word_alph(&self, word: &WordEntry) -> std::cmp::Ordering {
        let lc_word = word.word.to_lowercase().as_str().to_owned();
        let lc_self = self.word.to_lowercase().as_str().to_owned();

        lc_self.cmp(&lc_word)
    }

    pub fn _sort_pages(&mut self) {
        self.pages.sort()
    }
}

impl fmt::Display for WordEntry {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let mut pages = String::new();
        for page in 0..self.pages.len() {
            pages.push_str(&format!("{}", &self.pages[page]).to_string());
            if page < (self.pages.len() - 1) {
                pages.push_str(", ");
            }
        }
        write!(f, "{} ({}): {}", self.word, self.count, pages)
    }
}
