<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Ordner verwalten | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="webgroupware-email.php" title="27. Kapitel - E-Mail"><link rel="prev" href="webgroupware-email-send.php" title="27.2. E-Mails senden"><link rel="next" href="webgroupware-contacts.php" title="28. Kapitel - Adressbuch">
    <meta http-equiv="content-language" content="de">
  </head><body>
          
    <!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../index.html">
		<div id="logo_screen"><img src="../../../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../../../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="webgroupware-email-folder.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="webgroupware-email-folder.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/intranator.php">Business Server</a></li>
						<li><a href="../../../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../../../produkte/network_security.php">Network Security</a></li>
						<li><a href="../../../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../../../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../../../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../../../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../../../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../../../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../download/index.php">Software</a></li>
			<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../anfrage.php">Support-Anfrage</a></li>
			<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
			<li><a href="../../schulung.php">Schulung</a></li>
			<li><a href="../../fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../../../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../kaufen/index.php">Partner finden</a></li>
			<li><a href="../../../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../../../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->

    <div id="manual">
    <!-- content start -->

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">27.3. Ordner verwalten</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="webgroupware-email-send.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">27. Kapitel - E-Mail</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="webgroupware-contacts.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="webgroupware-email-folder"></a>27.3. Ordner verwalten</h2></div></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="webgroupware-email-folder-hierarchy"></a>27.3.1. Ordnerhierarchie</h3></div></div></div><p>In der linken Bildschrimh&auml;lfte wird die Liste aller E-Mail-Ordner angezeigt. Dabei
                wird der Wurzelordner des Benutzers (in IMAP "INBOX" genannt) ganz oben als
                    <code class="computeroutput">Posteingang</code> angezeigt. Darunter werden die
                Ordner f&uuml;r Entw&uuml;rfe, Gesendete E-Mails und Papierkorb angezeigt. Diese werden immer
                mit den Namen <code class="computeroutput">Entw&uuml;rfe</code>,
                    <code class="computeroutput">Gesendet</code> und
                    <code class="computeroutput">Papierkorb</code> angezeigt, unabh&auml;ngig davon, wie sie
                tats&auml;chlich benannt sind.</p><p>Der tats&auml;chliche Name dieser Ordner kann im Men&uuml;
                    <span class="guimenu">Benutzermanager&nbsp;&gt;&nbsp;Eigenes
                    Profil&nbsp;&gt;&nbsp;Groupware</span> bzw. vom Administrator im
                Men&uuml;
                    <span class="guimenu">Benutzermanager&nbsp;&gt;&nbsp;Benutzer&nbsp;:&nbsp;Groupware</span>
                konfiguriert werden.</p><p>Alle weiteren Unterordner des Benutzers werden unterhalb von
                    <span class="guimenu">Ordneraktionen</span> in alphabetischer Reihenfolge
                dargestellt.</p></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="webgroupware-email-folder-organize"></a>27.3.2. Ordner organisieren</h3></div></div></div><p>Die Ordnernamen in der Ordnerliste k&ouml;nnen mit der rechten Maustaste angeklickt
                werden. Es &ouml;ffnet sich ein Kontextmen&uuml;, welches Funktionen wie L&ouml;schen, Umbenennen
                oder das Erstellen von Unterordnern erlaubt.</p><p>Gesamte Ordner k&ouml;nnen per Drag&amp;Drop in der Ordnerhierarchie verschoben
                werden.</p><div class="screenshot"><div class="mediaobject"><img src="../images/webgroupware/email-folder-move.png"></div></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="webgroupware-email-folder-subscribe"></a>27.3.3. Ordner abonnieren</h3></div></div></div><p>Das Webmail-System zeigt normalerweise nur die abonnierten Ordner an, alle anderen
                Ordner sind ausgeblendet.</p><p>M&ouml;chten Sie einen Ordner abonnieren, schalten Sie zuerst auf die Ansicht aller
                Ordner um. Verwenden Sie dazu das Men&uuml;
                    <span class="guimenu">Ordneraktionen&nbsp;&gt;&nbsp;Alle Ordner
                    anzeigen</span>. Nun werden auch die nicht abonnieren Ordner angezeigt, diese
                werden mit kursivem Ordernamen dargestellt.</p><div class="screenshot"><div class="mediaobject"><img src="../images/webgroupware/email-folder-subscribe01.png"></div></div><p>Um einen Ordner zu abonnieren, &ouml;ffnen Sie mit der rechten Maustaste das
                Kontextmen&uuml; des entsprechenden Ordners und w&auml;hlen
                <span class="guimenu">Einblenden</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/webgroupware/email-folder-subscribe02.png"></div></div><p>Haben Sie alle gew&uuml;nschten Ordner abonniert, k&ouml;nnen Sie die nicht abonnierten
                Ordner &uuml;ber die Funktion
                    <span class="guimenu">Ordneraktionen&nbsp;&gt;&nbsp;Ausgeblendete Ordner
                    verstecken</span> wieder verstecken.</p><p>Die Liste der abonnierten Ordner wird auf dem IMAP-Server gespeichert. Die meisten
                E-Mail-Programme greifen auf diese serverseitige Abonnementliste zu. So muss ein
                Ordner nur einmal abonniert werden und er wird dann in allen verwendeten
                E-Mail-Programmen und Ger&auml;ten angezeigt.</p><p>Hat ein anderer Benutzer Ihnen einen seiner E-Mail-Ordner freigegeben, so ist
                dieser in der Hierarchie <code class="computeroutput">user</code> und darunter dem
                Benutzerlogin zu finden. Hat ein anderer Benutzer Ihnen seinen Posteingang
                freigegeben, so entspricht das dem Benutzernamen selbst; es wird kein Unterordner
                    <code class="computeroutput">Posteingang</code> angezeigt.</p><div class="screenshot"><div class="mediaobject"><img src="../images/webgroupware/email-folder-subscribe-others.png"></div></div><p>Freigegebene Ordner anderer Benutzer sind nach der Freigabe erst mal versteckt und
                m&uuml;ssen wie oben beschrieben abonniert werden bevor sie dauerhaft angezeigt
                werden.</p></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="webgroupware-email-folder-access"></a>27.3.4. Ordner freigeben</h3></div></div></div><p>Um Ordner f&uuml;r andere Benutzer freizugeben, klicken Sie den Ordnernamen in der
                Ordnerliste mit der rechten Maustaste an und &ouml;ffnen den Men&uuml;punkt <span class="guimenu">ACL
                    bearbeiten</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/webgroupware/email-folder-rights01.png"></div></div><p>Es &ouml;ffnet sich ein Fenster, in dem die Zugriffsrechte auf diesen Ordner im Detail
                bearbeitet werden k&ouml;nnen.</p><p>In der linken Spalte unter <span class="guilabel">Benutzer</span> k&ouml;nnen die Logins von
                anderen Benutzern eingegeben werden. Nach Eingabe des Benutzernamens k&ouml;nnen Sie
                entweder die IMAP-ACLs einzeln &uuml;ber die Kontrollk&auml;stchen steuern, oder Sie k&ouml;nnen
                h&auml;ufig verwendete Rechtekombinationen in den Vorlagen ausw&auml;hlen.</p><p>Soll ein Ordner nicht nur f&uuml;r einen Benutzer, sondern gleich f&uuml;r eine ganze
                Benutzergruppe freigegeben werden, so verwenden Sie als Benutzername
                    <strong class="userinput"><code>group:</code></strong> und dahinter den Namen der Benutzergruppe auf dem
                Intranator, also z.B. <strong class="userinput"><code>group:Alle</code></strong>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/webgroupware/email-folder-rights02.png"></div></div></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="webgroupware-email-send.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="webgroupware-email.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="webgroupware-contacts.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">27.2. E-Mails senden&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;28. Kapitel - Adressbuch</td></tr></table></div>
      
    <!-- content end -->
    </div>

  <!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../../../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../../../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../../../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../../../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../../../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../../../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../../../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../../../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../../../download/index.php">Software</a></li>
	<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="../../index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="../../anfrage.php">Support-Anfrage</a></li>
	<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
	<li><a href="../../schulung.php">Schulung</a></li>
	<li><a href="../../fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../../../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../../../kaufen/index.php">Partner finden</a></li>
	<li><a href="../../../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../../../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../../impressum.php">Impressum</a>
		<a href="../../../../en/developer/index.html">Entwickler</a>
		<a href="../../../datenschutz.php">Datenschutz</a>
		<a href="../../../unternehmen/kontakt.php">Kontakt</a>
	</div>
</div>

<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-151599-1']);
  _gaq.push(['_gat._anonymizeIp'])
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

<!-- PHP error counter: 0 -->

<!-- footer end -->

    </body></html>