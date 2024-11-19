#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <algorithm>

// Movie Class
class Movie
{
private:
    std::string title;
    std::string genre;
    std::string rating;
    int releaseYear;

public:
    Movie(const std::string &t, const std::string &g, const std::string &r, int y)
        : title(t), genre(g), rating(r), releaseYear(y) {}

    std::string getTitle() const { return title; }
    std::string getGenre() const { return genre; }
    std::string getRating() const { return rating; }
    int getReleaseYear() const { return releaseYear; }
};

// Iterator Interface
class Iterator
{
public:
    virtual ~Iterator() {}
    virtual bool hasNext() = 0;
    virtual Movie next() = 0;
};

// MovieCollection Class
class MovieCollection
{
private:
    std::vector<Movie> movies;

public:
    void addMovie(const Movie &movie)
    {
        movies.push_back(movie);
    }

    const std::vector<Movie> &getMovies() const
    {
        return movies;
    }
};

// GenreIterator Class
class GenreIterator : public Iterator
{
private:
    const std::vector<Movie> &movies;
    std::string genre;
    size_t position;

public:
    GenreIterator(const std::vector<Movie> &m, const std::string &g)
        : movies(m), genre(g), position(0) {}

    bool hasNext() override
    {
        while (position < movies.size())
        {
            if (movies[position].getGenre() == genre)
            {
                return true;
            }
            ++position;
        }
        return false;
    }

    Movie next() override
    {
        return movies[position++];
    }
};

// MultiGenreAndRatingIterator Class
class MultiGenreAndRatingIterator : public Iterator
{
private:
    const std::vector<Movie> &movies;
    std::vector<std::string> genres;
    std::string rating;
    size_t position;

public:
    MultiGenreAndRatingIterator(const std::vector<Movie> &m, const std::vector<std::string> &g, const std::string &r)
        : movies(m), genres(g), rating(r), position(0) {}

    bool hasNext() override
    {
        while (position < movies.size())
        {
            if (std::find(genres.begin(), genres.end(), movies[position].getGenre()) != genres.end() &&
                movies[position].getRating() == rating)
            {
                return true;
            }
            ++position;
        }
        return false;
    }

    Movie next() override
    {
        return movies[position++];
    }
};

// ReleaseYearFilterIterator Class
class ReleaseYearFilterIterator : public Iterator
{
private:
    const std::vector<Movie> &movies;
    int releaseYear;
    size_t position;

public:
    ReleaseYearFilterIterator(const std::vector<Movie> &m, int y)
        : movies(m), releaseYear(y), position(0) {}

    bool hasNext() override
    {
        while (position < movies.size())
        {
            if (movies[position].getReleaseYear() == releaseYear)
            {
                return true;
            }
            ++position;
        }
        return false;
    }

    Movie next() override
    {
        return movies[position++];
    }
};

// Client Code
int main()
{
    // Create a movie collection
    MovieCollection collection;
    collection.addMovie(Movie("Movie1", "Action", "PG-13", 2020));
    collection.addMovie(Movie("Movie2", "Drama", "R", 2019));
    collection.addMovie(Movie("Movie3", "Comedy", "PG", 2020));
    collection.addMovie(Movie("Movie4", "Action", "R", 2021));
    collection.addMovie(Movie("Movie5", "Drama", "PG-13", 2020));

    // Iterate over movies within a specific genre
    std::cout << "Movies in Action genre:\n";
    GenreIterator actionIterator(collection.getMovies(), "Action");
    while (actionIterator.hasNext())
    {
        Movie movie = actionIterator.next();
        std::cout << "- " << movie.getTitle() << " (" << movie.getReleaseYear() << ")\n";
    }

    // Iterate over movies across multiple genres with a specific rating
    std::cout << "\nMovies in Drama or Comedy genres with rating R:\n";
    MultiGenreAndRatingIterator multiIterator(collection.getMovies(), {"Drama", "Comedy"}, "R");
    while (multiIterator.hasNext())
    {
        Movie movie = multiIterator.next();
        std::cout << "- " << movie.getTitle() << " (" << movie.getReleaseYear() << ")\n";
    }

    // Filter movies by release year
    std::cout << "\nMovies released in 2020:\n";
    ReleaseYearFilterIterator yearIterator(collection.getMovies(), 2020);
    while (yearIterator.hasNext())
    {
        Movie movie = yearIterator.next();
        std::cout << "- " << movie.getTitle() << " (" << movie.getGenre() << ")\n";
    }

    return 0;
}
