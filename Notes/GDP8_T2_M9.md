# Level Design & Weapon Spawns
Today, we are going to be refining the existing body of work that we have and starting to form our gameplay loop
We might add a couple of new weapons to start showing some variety, but we won't be building the combat loop yet

This is for a couple of reasons. 
1. Our level is pretty small, so it would be nice to build something where we have more space to operate and create 
interesting/unique behaviors
2. Vertex, being primarily focused on Unreal Engine often neglects actual game design principals, so this will be an effort to kind of break that mold

That being said, we will try to implement some systems to facilitate the overall gameplay loop: Weapon spawning and player spawning variations
These both go into Level Design, so I think they're worth addressing now

## Level Design
So lets talk level design. First, there is a great resource called [The Level Design Book](https://book.leveldesignbook.com/)
It covers a LOT of topics related to level design including the process, the theory, the research and the psychology behind it

Now, I am not a level designer by trade, so I can't give you guys an in-depth dive into all of those topics, but today I will talk
about Map Balancing and layout. 

There are two perspectives when it comes to considering level design:
1. What we as the developer consider when building a level
2. What the player perceives as level design

In the former, this is the structured discipline of level design (how does it feel to play a map, what decision making goes into placing obstacles and buildings in particular places, and so one).
the discipline of level design is usually independent of aesthetics in terms of environment art, although they are related because the theme and scene should inform the level design as well as the aesthetics
The Player's perspective will consume the aesthetics and gameplay feel as the core element of level design. How it looks and feels to them is what Level Design is to a player

Level design also differs signficantly when considering a PvP game or a PvE game. PvP games are, of course, adversarial and only one team can win, but its incredibly important that all teams feel that the chance to win is equal. Single player games, on the other hand, are designed so that the player will eventually win, so level design between PvE and PvP contains some very different approaches.

## Multiplayer Level Design
Since our game is a local multiplayer-type game, we'll be looking at the PvP aspect.

The most important thing when designing a level for PvP is the fairness. Like I mentioned earlier, each team needs to feel that they have an equal and real possibility of winning. There also cannot be one
consistent strategy for winning, called a dominant strategy. If a dominant strategy arises, all reasonable players will defer to that strategy which will make the game feel repetitive and boring.
In a lot of multiplayer games there are some strategies that are slightly better but not dominating, this is how we get "meta" gameplay loops. This is where balancing comes into play, but balancing is another large topic all on its own, so we aren't really going to cover it here outside of what it means in terms of level design.
Level design is an iterative process so you aren't likely to get a well-balanced map on your first attempt.
When balancing a level, we can focus on 
1. The Layout: the overall structure of the map.
2. The Blockout: a low resolution implementation of a level. For our 2D game, this isn't going to be too far off from our actual implementation, but for a 3D game with high resolution assets, blockout iterations are a cost-effective way to experiment without wasting artists' time and resources
3. Player Feedback

When tuning a level for balance, we may be tweaking the layout and adjusting how the gameplay feels while moving about the environment.
When adjusting the blockout, we are changing distances between elements, the amount of cover a player can hide behind, the angles of visibility.

Even small changes can have a big impact on the actual gameplay elements. Things like Jump Distance when addressing verticality can be used to adjust the viability of a particular play strategy.

Discuss Symmetry and Asymmetry in regards to map layout
Symmetry is easy. Each team gets the same layout on their side of the map with a common area in between where most of the player engagements are likely to occur.
Asymmetry is hard to get right but can provide a much more interesting gameplay interaction by having unique environments on different ends of the map

So, for the map we're going to build today, I wanted a larger map where we can get some variety in. This one will be symmetrical for simplicity, but we will encourage riskier player behavior by putting more powerful weapons in hard to reach or easily contested places